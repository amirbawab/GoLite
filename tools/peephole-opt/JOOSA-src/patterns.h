/*
 * JOOS is Copyright (C) 1997 Laurie Hendren & Michael I. Schwartzbach
 *
 * Reproduction of all or part of this software is permitted for
 * educational or research use on condition that this copyright notice is
 * included in any copy. This software comes with no warranty of any
 * kind. In no event will the authors be liable for any damages resulting from
 * use of this software.
 *
 * email: hendren@cs.mcgill.ca, mis@brics.dk
 */

/* iload x        iload x        iload x
 * ldc 0          ldc 1          ldc 2
 * imul           imul           imul
 * ------>        ------>        ------>
 * ldc 0          iload x        iload x
 *                               dup
 *                               iadd
 */
int simplify_multiplication(CODE **c) {
    int x, k;
    if (is_imul(next(next(*c)))) {
        if((is_iload(*c, &x)
           && is_ldc_int(next(*c), &k))
           || (is_ldc_int(*c, &k)
              && is_iload(next(*c), &x))) {
            if (k == 0) return replace(c, 3, makeCODEldc_int(0, NULL));
            if (k == 1) return replace(c, 3, makeCODEiload(x, NULL));
            if (k == 2) return replace(c, 3, makeCODEiload(x, makeCODEdup(makeCODEiadd(NULL))));
        }
    }
    return 0;
}

/* iload x
 * ldc 0
 * iadd
 * ------>
 * iload x
 */
int simplify_addition(CODE **c) {
    int x, k;
    if (is_iadd(next(next(*c)))) {
        if((is_iload(*c, &x)
           && is_ldc_int(next(*c), &k))
           || (is_ldc_int(*c, &k)
              && is_iload(next(*c), &x))) {
            if(k == 0) return replace(c, 3, makeCODEiload(x, NULL));
        }
    }
    return 0;
}

/* iload x
 * ldc 0
 * isub
 * ------>
 * iload x
 */
int simplify_subtract_left(CODE **c) {
    int x, k;
    if (is_iload(*c, &x)
        && is_ldc_int(next(*c), &k)
        && is_isub(next(next(*c)))
        && k == 0) {
        return replace(c, 3, makeCODEiload(x, NULL));
    }
    return 0;
}

/* iload x
 * iload x
 * isub
 * ------>
 * ldc 0
 */
int simplify_self_subtract(CODE **c) {
    int x, k;
    if (is_iload(*c, &x)
        && is_iload(next(*c), &k)
        && is_isub(next(next(*c)))
        && x == k) {
        return replace(c, 3, makeCODEldc_int(0, NULL));
    }
    return 0;
}

/* iload x
 * ldc 1
 * idiv
 * ------>
 * iload x
 */

int simplify_division_right(CODE **c) {
    int x, k;
    if (is_iload(*c, &x)
        && is_ldc_int(next(*c), &k)
        && is_idiv(next(next(*c)))
        && k == 1) {
        return replace(c, 3, makeCODEiload(x, NULL));
    }
    return 0;
}

/* dup
 * astore x
 * pop
 * -------->
 * astore x
 */
int simplify_astore(CODE **c) {
    int x;
    if (is_dup(*c)
        && is_astore(next(*c), &x)
        && is_pop(next(next(*c)))) {
        return replace(c, 3, makeCODEastore(x, NULL));
    }
    return 0;
}

/* dup
 * istore x
 * pop
 * -------->
 * istore x
 */
int simplify_istore(CODE **c) {
    int x;
    if (is_dup(*c)
        && is_istore(next(*c), &x)
        && is_pop(next(next(*c)))) {
        return replace(c, 3, makeCODEistore(x, NULL));
    }
    return 0;
}

/* iload x
 * ldc k   (0<=k<=127)
 * iadd
 * istore x
 * --------->
 * iinc x k
 */
int positive_increment(CODE **c) {
    int x, y, k;
    if (is_iload(*c, &x)
        && is_ldc_int(next(*c), &k)
        && is_iadd(next(next(*c)))
        && is_istore(next(next(next(*c))), &y)
        && x == y
        && 0 <= k
        && k <= 127) {
        return replace(c, 4, makeCODEiinc(x, k, NULL));
    }
    return 0;
}

/* iload x
 * ldc k   (-128<=k<0)
 * iadd
 * istore x
 * --------->
 * iinc x k
 */
int negative_increment(CODE **c) {
    int x, y, k;
    if (is_iload(*c, &x)
        && is_ldc_int(next(*c), &k)
        && is_iadd(next(next(*c)))
        && is_istore(next(next(next(*c))), &y)
        && x == y
        && -128 <= k
        && k < 0) {
        return replace(c, 4, makeCODEiinc(x, k, NULL));
    }
    return 0;
}

/* goto L1
 * ...
 * L1:
 * goto L2
 * ...
 * L2:
 * --------->
 * goto L2
 * ...
 * L1:    (reference count reduced by 1)
 * goto L2
 * ...
 * L2:    (reference count increased by 1)  
 */
int simplify_goto_goto(CODE **c) {
    int l1, l2;
    if (is_goto(*c, &l1)
        && is_goto(next(destination(l1)), &l2)
        && l1 > l2) {
        droplabel(l1);
        copylabel(l2);
        return replace(c, 1, makeCODEgoto(l2, NULL));
    }
    return 0;
}

/* iload x
 * ldc 0
 * if_icmpeq
 * --------->
 * iload x
 * if_eq
 */
int simplify_ibranch(CODE **c) {
    int x1, x2, x3;
    if ((is_iload(*c, &x1)
        && is_ldc_int(next(*c), &x2))
        || (is_ldc_int(*c, &x2)
           && is_iload(next(*c), &x1))) {
        if(x2 == 0) {
            if(is_if_icmpeq(next(next(*c)), &x3))
                return replace(c, 3, makeCODEiload(x1, makeCODEifeq(x3, NULL)));
            if(is_if_icmpne(next(next(*c)), &x3))
                return replace(c, 3, makeCODEiload(x1, makeCODEifne(x3, NULL)));
        }
    }
    return 0;
}

/* aload x
 * aconst_null
 * if_acmpeq
 * --------->
 * aload x
 * ifnull
 */
int simplify_abranch(CODE **c) {
    int x1, x2;
    if ((is_aload(*c, &x1)
        && is_aconst_null(next(*c)))
        || (is_aconst_null(*c)
           && is_aload(next(*c), &x1))) {
        if (is_if_acmpeq(next(next(*c)), &x2))
            return replace(c, 3, makeCODEaload(x1, makeCODEifnull(x2, NULL)));
        if (is_if_acmpne(next(next(*c)), &x2))
            return replace(c, 3, makeCODEaload(x1, makeCODEifnonnull(x2, NULL)));
    }
    return 0;
}

/**
 * if_acmpeq true_2     <-- reduce label
 * iconst_0
 * goto stop_3          <-- reduce label
 * true_2:
 * iconst_1
 * stop_3:
 * ifeq else_0
 * ------------>
 * if_acmpne else_0
 */
int simplify_if_branch(CODE **c) {
    int x1, x2, x3, x4, x5, x6, x7;
    if (is_ldc_int(next(*c), &x2)
        && x2 == 0
        && is_goto(next(next(*c)), &x3)
        && is_label(next(next(next(*c))), &x4)
        && is_ldc_int(next(next(next(next(*c)))), &x5)
        && x5 == 1
        && is_label(next(next(next(next(next(*c))))), &x6)
        && x3 == x6
        && is_ifeq(next(next(next(next(next(next(*c)))))), &x7)) {
        if(is_if_acmpeq(*c, &x1)) {
            droplabel(x1);
            droplabel(x3);
            return replace(c, 7, makeCODEif_acmpne(x7, NULL));
        }
        if(is_if_acmpne(*c, &x1)) {
            droplabel(x1);
            droplabel(x3);
            return replace(c, 7, makeCODEif_acmpeq(x7, NULL));
        }
        if(is_if_icmpeq(*c, &x1)) {
            droplabel(x1);
            droplabel(x3);
            return replace(c, 7, makeCODEif_icmpne(x7, NULL));
        }
        if(is_if_icmpne(*c, &x1)) {
            droplabel(x1);
            droplabel(x3);
            return replace(c, 7, makeCODEif_icmpeq(x7, NULL));
        }
        if(is_if_icmplt(*c, &x1)) {
            droplabel(x1);
            droplabel(x3);
            return replace(c, 7, makeCODEif_icmpge(x7, NULL));
        }
        if(is_if_icmple(*c, &x1)) {
            droplabel(x1);
            droplabel(x3);
            return replace(c, 7, makeCODEif_icmpgt(x7, NULL));
        }
        if(is_if_icmpgt(*c, &x1)) {
            droplabel(x1);
            droplabel(x3);
            return replace(c, 7, makeCODEif_icmple(x7, NULL));
        }
        if(is_if_icmpge(*c, &x1)) {
            droplabel(x1);
            droplabel(x3);
            return replace(c, 7, makeCODEif_icmplt(x7, NULL));
        }
        if(is_if_icmpge(*c, &x1)) {
            droplabel(x1);
            droplabel(x3);
            return replace(c, 7, makeCODEif_icmplt(x7, NULL));
        }
    }
    return 0;
}

/**
 * goto A
 * ...
 * goto B
 * ...
 * A:
 * B:
 * --------->
 * goto B
 * ...
 * goto B
 * ...
 * A:  <--- Will be removed by another pattern
 * B:
 */
int merge_labels(CODE **c) {
    int x1, x2, x3;
    if (is_goto(*c, &x1)) {
        CODE* nextCode = *c;
        while((nextCode = next(nextCode))) {
            if(is_label(nextCode, &x2)
               && x1 == x2
               && is_label(next(nextCode), &x3)) {
                droplabel(x1);
                copylabel(x3);
                return replace(c, 1, makeCODEgoto(x3, NULL));
            }
        }
    }
    return 0;
}

/**
 * .....
 * label: <-- Not used, remove it
 * .....
 */
int remove_dead_labels(CODE **c) {
    int x1;
    if(is_label(*c, &x1) && deadlabel(x1)) {
        return replace(c, 1,  NULL);
    }
    return 0;
}

/**
 * ldc x
 * istore
 * ldc x
 */
int simplify_ldc_store(CODE **c) {
    int x1, x2, x3;
    if(is_ldc_int(*c, &x1)
       && is_ldc_int(next(next(*c)), &x3)
       && x1 == x3) {
        if(is_istore(next(*c), &x2)) {
            return replace(c, 3, makeCODEldc_int(x1,makeCODEdup(makeCODEistore(x2, NULL))));
        }
        if(is_astore(next(*c), &x2)) {
            return replace(c, 3, makeCODEldc_int(x1,makeCODEdup(makeCODEastore(x2, NULL))));
        }
    }
    return 0;
}

/**
 * ireturn
 * nop
 * -------->
 * ireturn
 */
int remove_nop(CODE **c) {
    if(is_nop(next(*c))) {
        if(is_ireturn(*c)){
            return replace(c, 2, makeCODEireturn(NULL));
        }
        if(is_areturn(*c)){
            return replace(c, 2, makeCODEareturn(NULL));
        }
    }
    return 0;
}

void init_patterns(void) {
    /*Given optimization*/
    ADD_PATTERN(positive_increment);
    ADD_PATTERN(simplify_istore);
    ADD_PATTERN(simplify_astore);
    ADD_PATTERN(negative_increment);
    ADD_PATTERN(simplify_multiplication);
    ADD_PATTERN(simplify_division_right);
    ADD_PATTERN(simplify_subtract_left);
    ADD_PATTERN(simplify_self_subtract);
    ADD_PATTERN(simplify_addition);
    ADD_PATTERN(simplify_if_branch);
    ADD_PATTERN(simplify_ibranch);
    ADD_PATTERN(simplify_abranch);
    ADD_PATTERN(merge_labels);
    ADD_PATTERN(simplify_goto_goto);
    ADD_PATTERN(simplify_ldc_store);
    ADD_PATTERN(remove_nop);
    /*ADD_PATTERN(remove_dead_labels);*/ /*This causes an error when simplify_if_branch is enabled*/
}