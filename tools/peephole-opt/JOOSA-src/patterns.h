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

/**
 * Helper function
 * Check if function is an if statement and set label
 */
int is_if_code(CODE* code, int *label) {
    return is_if_acmpeq(code, label)
           || is_if_acmpne(code, label)
           || is_if_icmpeq(code, label)
           || is_if_icmpne(code, label)
           || is_if_icmplt(code, label)
           || is_if_icmple(code, label)
           || is_if_icmpgt(code, label)
           || is_if_icmpge(code, label)
           || is_ifeq(code, label)
           || is_ifne(code, label)
           || is_ifnull(code, label)
           || is_ifnonnull(code, label);
}

/**
 * Helper function
 * Get function corresponding to the if statement code
 */
int (*code_to_if(CODE* c))(CODE*, int*) {
    int x1;
    if(is_if_acmpeq(c, &x1)) {
        return is_if_acmpeq;
    }
    if(is_if_acmpne(c, &x1)) {
        return is_if_acmpne;
    }
    if(is_if_icmpeq(c, &x1)) {
        return is_if_icmpeq;
    }
    if(is_if_icmpne(c, &x1)) {
        return is_if_icmpne;
    }
    if(is_if_icmplt(c, &x1)) {
        return is_if_icmplt;
    }
    if(is_if_icmple(c, &x1)) {
        return is_if_icmple;
    }
    if(is_if_icmpgt(c, &x1)) {
        return is_if_icmpgt;
    }
    if(is_if_icmpge(c, &x1)) {
        return is_if_icmpge;
    }
    if(is_ifeq(c, &x1)) {
        return is_ifeq;
    }
    if(is_ifne(c, &x1)) {
        return is_ifne;
    }
    if(is_ifnull(c, &x1)) {
        return is_ifnull;
    }
    if(is_ifnonnull(c, &x1)) {
        return is_ifnonnull;
    }
    return NULL;
}

/**
 * Helper functions
 * Make code for the corresponding if statement
 */
CODE* if_to_make(int (*func_is)(CODE*, int*), int label, CODE *next) {
    if(func_is == is_if_acmpeq) {
        return makeCODEif_acmpeq(label, next);
    }
    if(func_is == is_if_acmpne) {
        return makeCODEif_acmpne(label, next);
    }
    if(func_is == is_if_icmpeq) {
        return makeCODEif_icmpeq(label, next);
    }
    if(func_is == is_if_icmpne) {
        return makeCODEif_icmpne(label, next);
    }
    if(func_is == is_if_icmplt) {
        return makeCODEif_icmplt(label, next);
    }
    if(func_is == is_if_icmple) {
        return makeCODEif_icmple(label, next);
    }
    if(func_is == is_if_icmpgt) {
        return makeCODEif_icmpgt(label, next);
    }
    if(func_is == is_if_icmpge) {
        return makeCODEif_icmpge(label, next);
    }
    if(func_is == is_ifeq) {
        return makeCODEifeq(label, next);
    }
    if(func_is == is_ifne) {
        return makeCODEifne(label, next);
    }
    if(func_is == is_ifnull) {
        return makeCODEifnull(label, next);
    }
    if(func_is == is_ifnonnull) {
        return makeCODEifnonnull(label, next);
    }
    return NULL;
}

/**
 * Helper functions
 * Make code for the corresponding opposite if statement
 */
CODE* if_to_opposite_make(int (*func_is)(CODE*, int*), int label, CODE *next) {
    if(func_is == is_if_acmpeq) {
        return if_to_make(is_if_acmpne, label, next);
    }
    if(func_is == is_if_acmpne) {
        return if_to_make(is_if_acmpeq, label, next);
    }
    if(func_is == is_if_icmpeq) {
        return if_to_make(is_if_icmpne, label, next);
    }
    if(func_is == is_if_icmpne) {
        return if_to_make(is_if_icmpeq, label, next);
    }
    if(func_is == is_if_icmplt) {
        return if_to_make(is_if_icmpge, label, next);
    }
    if(func_is == is_if_icmple) {
        return if_to_make(is_if_icmpgt, label, next);
    }
    if(func_is == is_if_icmpgt) {
        return if_to_make(is_if_icmple, label, next);
    }
    if(func_is == is_if_icmpge) {
        return if_to_make(is_if_icmplt, label, next);
    }
    if(func_is == is_ifeq) {
        return if_to_make(is_ifne, label, next);
    }
    if(func_is == is_ifne) {
        return if_to_make(is_ifeq, label, next);
    }
    if(func_is == is_ifnull) {
        return if_to_make(is_ifnonnull, label, next);
    }
    if(func_is == is_ifnonnull) {
        return if_to_make(is_ifnull, label, next);
    }
    return NULL;
}

/**
 * Helper function
 * Check if code is an integer operand
 */
int is_ioperand(CODE* c, int *arg) {
    return is_ldc_int(c, arg)
           || is_iload(c, arg);
}

/**
 * Helper function
 * Make code for integer operand
 */
CODE* ioperand_to_make(int (*func_is)(CODE*, int*), int arg, CODE *next) {
    if(func_is == is_ldc_int) {
        return makeCODEldc_int(arg, next);
    }
    if(func_is == is_iload) {
        return makeCODEiload(arg, next);
    }
    return NULL;
}

/**
 * Helper function
 * Get function corresponding to integer operand
 */
int (*code_to_ioperand(CODE* c))(CODE*, int*) {
    int x1;
    if (is_iload(c, &x1)) {
        return is_iload;
    }
    if (is_ldc_int(c, &x1)) {
        return is_ldc_int;
    }
    return NULL;
}

/**
 * Helper function
 * Check if code is a load
 */
int is_load(CODE* c, int *arg) {
    return is_ioperand(c, arg)
           || is_aload(c, arg);
}

/**
 * Helper function
 * Make code for load statement
 */
CODE* load_to_make(int (*func_is)(CODE*, int*), int arg, CODE *next) {
    if(func_is == is_ldc_int) {
        return makeCODEldc_int(arg, next);
    }
    if(func_is == is_iload) {
        return makeCODEiload(arg, next);
    }
    if(func_is == is_aload) {
        return makeCODEaload(arg, next);
    }
    return NULL;
}

/**
 * Helper function
 * Get function for corresponding load statement
 */
int (*code_to_load(CODE* c))(CODE*, int*) {
    int x1;
    if (is_iload(c, &x1)) {
        return is_iload;
    }
    if (is_aload(c, &x1)) {
        return is_aload;
    }
    if (is_ldc_int(c, &x1)) {
        return is_ldc_int;
    }
    return NULL;
}

/*----- END OF HELPER FUNCTIONS ------*/

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

/* iload x      ldc 0
 * ldc 0        iload x
 * iadd         iadd
 * ------>      ------>
 * iload x      iload x
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
 * ldc k   (0>=k>128)
 * isub
 * istore x
 * --------->
 * iinc x -k
 */
int negative_increment(CODE **c) {
    int x, y, k;
    if (is_iload(*c, &x)
        && is_ldc_int(next(*c), &k)
        && is_isub(next(next(*c)))
        && is_istore(next(next(next(*c))), &y)
        && x == y
        && 0 <= k
        && k <= 127) {
        return replace(c, 4, makeCODEiinc(x, -k, NULL));
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

/**
 * APPLIED FOR BOTH if_icmpeq and if_icmpne
 *
 * iload x          ldc 0
 * ldc 0            iload x
 * if_icmpeq        if_icmpeq
 * --------->       --------->
 * iload x          iload x
 * if_eq            if_eq
 */
int simplify_branch_3(CODE **c) {
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

/* aload x          aload x
 * aconst_null      aconst_null
 * if_acmpeq        if_acmpne
 * --------->       ----------->
 * aload x          aload x
 * ifnull           ifnonnull
 */
int simplify_branch_2(CODE **c) {
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
 * APPLIED FOR ALL FORMS OF IF
 *
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
int simplify_branch_1(CODE **c) {
    int x1, x2, x3, x4, x5, x6, x7;
    if (is_if_code(*c, &x1)
        && is_ldc_int(next(*c), &x2)
        && x2 == 0
        && is_goto(next(next(*c)), &x3)
        && is_label(next(next(next(*c))), &x4)
        && x1 == x4
        && currentlabels[x1].sources == 1
        && is_ldc_int(next(next(next(next(*c)))), &x5)
        && x5 == 1
        && is_label(next(next(next(next(next(*c))))), &x6)
        && x3 == x6
        && currentlabels[x6].sources == 1
        && is_ifeq(next(next(next(next(next(next(*c)))))), &x7)) {
        droplabel(x1);
        droplabel(x3);
        return replace(c, 7, if_to_opposite_make(code_to_if(*c), x7, NULL));
    }
    return 0;
}

/**
 * APPLIED FOR ALL FORMS OF IF
 *
 * ifeq true        <-- reduce label
 * goto else
 * true:
 * ---------->
 * ifne else
 */
int simplify_branch_4(CODE **c) {
    int x1, x2, x3;
    if(is_if_code(*c, &x1)
       &&is_goto(next(*c), &x2)
       && is_label(next(next(*c)), &x3)
       && currentlabels[x1].sources == 1) {
        droplabel(x1);
        return replace(c, 3, if_to_opposite_make(code_to_if(*c), x2, NULL));
    }
    return 0;
}

/**
 * acsont_null      aconst_null
 * if_acmpeq        if_acmpne
 * ---------->      ---------->
 * ifnull           ifnonnull
 */
int simplify_branch_6(CODE **c) {
    int x1;
    if(is_aconst_null(*c)) {
        if(is_if_acmpeq(next(*c), &x1)) {
            return replace(c, 2, makeCODEifnull(x1, NULL));
        }
        if(is_if_acmpne((next(*c)), &x1)) {
            return replace(c, 2, makeCODEifnonnull(x1, NULL));
        }
    }
    return 0;
}

/**
 * iconst_0         iconst_0
 * if_icmpeq        if_icmpne
 * ---------->      ---------->
 * ifeq             ifne
 */
int simplify_branch_7(CODE **c) {
    int x1, x2;
    if(is_ldc_int(*c, &x1)
       && x1 == 0) {
        if(is_if_icmpeq(next(*c), &x2)) {
            return replace(c, 2, makeCODEifeq(x2, NULL));
        }
        if(is_if_icmpne((next(*c)), &x2)) {
            return replace(c, 2, makeCODEifne(x2, NULL));
        }
    }
    return 0;
}

/**
 * iload_3
 * ifeq true_38
 * iconst_0
 * goto stop_39
 * true_38:
 * iconst_1
 * stop_39:
 * dup
 * ifeq false_37
 * pop
 * ------------>
 * iconst_0
 * iload_3
 * ifne false_37
 * pop
 */
int simplify_branch_8(CODE **c) {
    int x1,x2,x3,x4,x5,x6,x7,x8;
    if (is_ioperand(*c, &x1)
        && is_ifeq(next(*c), &x2)
        && is_ldc_int(next(next(*c)), &x3)
        && is_goto(next(next(next(*c))), &x4)
        && is_label(next(next(next(next(*c)))), &x5)
        && x2 == x5
        && currentlabels[x5].sources == 1
        && is_ldc_int(next(next(next(next(next(*c))))), &x6)
        && is_label(next(next(next(next(next(next(*c)))))), &x7)
        && x4 == x7
        && currentlabels[x7].sources == 1
        && is_dup(next(next(next(next(next(next(next(*c))))))))
        && is_ifeq(next(next(next(next(next(next(next(next(*c)))))))), &x8)
        && is_pop(next(next(next(next(next(next(next(next(next(*c))))))))))) {
        return replace(c, 10, makeCODEldc_int(x3, ioperand_to_make(code_to_ioperand(*c), x1, makeCODEifne(x8, makeCODEpop(NULL)))));
    }
    return 0;
}

/**
 * iload_2
 * iconst_4
 * if_icmpeq true_14
 * iconst_0
 * goto true_11
 * true_14:
 * iconst_1
 * true_11:
 * dup
 * ifeq true_10
 * pop
 * ---------->
 * iconst_0
 * iload_2
 * iconst_4
 * if_ifcmpne ture_10
 * pop
 */
int simplify_branch_9(CODE **c) {
    int x0,x1,x2,x3,x4,x5,x6,x7,x8;
    if (is_ioperand(*c, &x0)
        && is_ioperand(next(*c), &x1)
        && is_if_code(next(next(*c)), &x2)
        && is_ldc_int(next(next(next(*c))), &x3)
        && is_goto(next(next(next(next(*c)))), &x4)
        && is_label(next(next(next(next(next(*c))))), &x5)
        && x2 == x5
        && currentlabels[x5].sources == 1
        && is_ldc_int(next(next(next(next(next(next(*c)))))), &x6)
        && is_label(next(next(next(next(next(next(next(*c))))))), &x7)
        && x4 == x7
        && currentlabels[x7].sources == 1
        && is_dup(next(next(next(next(next(next(next(next(*c)))))))))
        && is_ifeq(next(next(next(next(next(next(next(next(next(*c))))))))), &x8)
        && is_pop(next(next(next(next(next(next(next(next(next(next(*c)))))))))))) {
        return replace(c, 11, makeCODEldc_int(x3, ioperand_to_make(code_to_ioperand(*c), x0, ioperand_to_make(code_to_ioperand(next(*c)), x1, if_to_opposite_make(code_to_if(next(next(*c))), x8, makeCODEpop(NULL))))));
    }
    return 0;
}

/**
 * goto A   <-- reduce label
 * ...
 * goto B   <-- increase label
 * ...
 * A:
 * B:
 * --------->
 * goto B
 * ...
 * goto B
 * ...
 * A:
 * B:
 */
int merge_labels(CODE **c) {
    int x1, x2;
    if (uses_label(*c, &x1)) {
        if(is_label(next(destination(x1)), &x2)) {
            droplabel(x1);
            copylabel(x2);
            if(is_goto(*c, &x1)) {
                return replace(c, 1, makeCODEgoto(x2, NULL));
            }
            if(is_if_code(*c, &x1)) {
                return replace(c, 1, if_to_make(code_to_if(*c), x2, NULL));
            }
        }
    }
    return 0;
}

/**
 * ldc x
 * istore
 * ldc x
 * -------->
 * ldc x
 * dup
 * istore
 */
int simplify_ldc_istore(CODE **c) {
    int x1, x2, x3;
    if(is_ldc_int(*c, &x1)
       && is_istore(next(*c), &x2)
       && is_ldc_int(next(next(*c)), &x3)
       && x1 == x3) {
        return replace(c, 3, makeCODEldc_int(x1,makeCODEdup(makeCODEistore(x2, NULL))));
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
        if(is_return(*c)) {
            return replace(c, 2, makeCODEreturn(NULL));
        }
    }
    return 0;
}

/**
 * dup
 * aload
 * swap
 * putfield
 * pop
 * --------->
 * aload
 * swap
 * putfield
 */
int simplify_putfield(CODE **c) {
    int x1;
    char *x2;
    if(is_dup(*c)
       && is_aload(next(*c), &x1)
       && is_swap(next(next(*c)))
       && is_putfield(next(next(next(*c))),&x2)
       && is_pop(next(next(next(next(*c)))))) {
        return replace(c, 5, makeCODEaload(x1, makeCODEswap(makeCODEputfield(x2, NULL))));
    }
    return 0;
}

/**
 * ldc | load
 * ldc | load
 * swap
 * ----->
 * ldc | load
 * ldc | load
 */
int simplify_swap_1(CODE **c) {
    int x1, x2;
    char* y1, *y2;
    if(is_swap(next(next(*c)))) {
        if(is_load(*c, &x1)
           && is_load(next(*c), &x2)) {
            return replace(c, 3, load_to_make(code_to_load(next(*c)), x2, load_to_make(code_to_load(*c), x1, NULL)));
        }
        if(is_ldc_string(*c, &y1)
           && is_ldc_string(next(*c), &y2)) {
            return replace(c, 3, makeCODEldc_string(y2, makeCODEldc_string(y1, NULL)));
        }
        if(is_load(*c, &x1)
           && is_ldc_string(next(*c), &y1)) {
            return replace(c, 3, makeCODEldc_string(y1, load_to_make(code_to_load(*c), x1, NULL)));
        }
        if(is_ldc_string(*c, &y1)
           && is_load(next(*c), &x1)) {
            return replace(c, 3, load_to_make(code_to_load(next(*c)), x1, makeCODEldc_string(y1, NULL)));
        }
    }
    return 0;
}

/**
 * new
 * dup
 * invokenonvirtual
 * aload_0
 * swap
 * putfield
 * ----------->
 * aload_0
 * new
 * dup
 * invokenonvirtual
 * putfield
 */
int simplify_swap_2(CODE **c) {
    int x1;
    char *y1, *y2, *y3;
    if(is_new(*c, &y1)
       && is_dup(next(*c))
       && is_invokenonvirtual(next(next(*c)), &y2)
       && is_aload(next(next(next(*c))), &x1)
       && is_swap(next(next(next(next(*c)))))
       && is_putfield(next(next(next(next(next(*c))))), &y3)) {
        return replace(c, 6, makeCODEaload(x1, makeCODEnew(y1, makeCODEdup(makeCODEinvokenonvirtual(y2, makeCODEputfield(y3, NULL))))));
    }
    return 0;
}

/**
 * aload 0
 * getfield
 * aload 0
 * swap
 * -------->
 * aload 0
 * aload 0
 * getfield
 */
int simplify_swap_3(CODE **c) {
    int x1, x2;
    char *y1;
    if(is_aload(*c, &x1)
       && is_getfield(next(*c), &y1)
       && is_aload(next(next(*c)), &x2)
       && is_swap(next(next(next(*c))))) {
        return replace(c, 4, makeCODEaload(x1, makeCODEaload(x2, makeCODEgetfield(y1, NULL))));
    }
    return 0;
}

/**
 * new
 * dup
 * ldc | load
 * invokenonvirtual
 * aload_0
 * swap
 * putfield
 * ----------->
 * aload_0
 * new
 * dup
 * ldc | load
 * invokenonvirtual
 * putfield
 */
int simplify_swap_4(CODE **c) {
    int x1, x2;
    char *y1, *y2, *y3, *y4;
    if(is_new(*c, &y1)
       && is_dup(next(*c))
       && is_invokenonvirtual(next(next(next(*c))), &y2)
       && is_aload(next(next(next(next(*c)))), &x1)
       && is_swap(next(next(next(next(next(*c))))))
       && is_putfield(next(next(next(next(next(next(*c)))))), &y3)) {
        if(is_load(next(next(*c)), &x2)) {
            return replace(c, 7, makeCODEaload(x1, makeCODEnew(y1, makeCODEdup(load_to_make(code_to_load(next(next(*c))), x2, makeCODEinvokenonvirtual(y2, makeCODEputfield(y3, NULL)))))));
        }
        if(is_ldc_string(next(next(*c)), &y4)) {
            return replace(c, 7, makeCODEaload(x1, makeCODEnew(y1, makeCODEdup(makeCODEldc_string(y4, makeCODEinvokenonvirtual(y2, makeCODEputfield(y3, NULL)))))));
        }
    }
    return 0;
}

/**
 * new
 * dup
 * ldc | load
 * ldc | load
 * invokenonvirtual
 * aload_0
 * swap
 * putfield
 * ----------->
 * aload_0
 * new
 * dup
 * ldc | load
 * ldc | load
 * invokenonvirtual
 * putfield
 */
int simplify_swap_5(CODE **c) {
    int x1, x2, x3;
    char *y1, *y2, *y3, *y4, *y5;
    if(is_new(*c, &y1)
       && is_dup(next(*c))
       && is_invokenonvirtual(next(next(next(next(*c)))), &y2)
       && is_aload(next(next(next(next(next(*c))))), &x1)
       && is_swap(next(next(next(next(next(next(*c)))))))
       && is_putfield(next(next(next(next(next(next(next(*c))))))), &y3)) {
        if(is_ldc_string(next(next(*c)), &y4)
           && is_ldc_string(next(next(next(*c))), &y5)) {
            return replace(c, 8, makeCODEaload(x1, makeCODEnew(y1, makeCODEdup(makeCODEldc_string(y4, makeCODEldc_string(y5, makeCODEinvokenonvirtual(y2, makeCODEputfield(y3, NULL))))))));
        }
        if(is_load(next(next(*c)), &x2)
           && is_load(next(next(next(*c))), &x3)) {
            return replace(c, 8, makeCODEaload(x1, makeCODEnew(y1, makeCODEdup(load_to_make(code_to_load(next(next(*c))), x2, load_to_make(code_to_load(next(next(next(*c)))), x3, makeCODEinvokenonvirtual(y2, makeCODEputfield(y3, NULL))))))));
        }
        if(is_ldc_string(next(next(*c)), &y4)
           && is_load(next(next(next(*c))), &x2)) {
            return replace(c, 8, makeCODEaload(x1, makeCODEnew(y1, makeCODEdup(makeCODEldc_string(y4, load_to_make(code_to_load(next(next(next(*c)))), x2, makeCODEinvokenonvirtual(y2, makeCODEputfield(y3, NULL))))))));
        }
        if(is_load(next(next(*c)), &x2)
           && is_ldc_string(next(next(next(*c))), &y4)) {
            return replace(c, 8, makeCODEaload(x1, makeCODEnew(y1, makeCODEdup(load_to_make(code_to_load(next(next(*c))), x2, makeCODEldc_string(y4, makeCODEinvokenonvirtual(y2, makeCODEputfield(y3, NULL))))))));
        }
    }
    return 0;
}

/**
 * ldc "..."
 * dup
 * ifnonnull stop   <-- reduce label
 * pop
 * ldc "null"
 * stop
 * ------------->
 * ldc "..."
 */
int simplify_string(CODE **c) {
    int x1, x2;
    char *y1, *y2;
    if(is_ldc_string(*c, &y1)
       && is_dup(next(*c))
       && is_ifnonnull(next(next(*c)), &x1)
       && is_pop(next(next(next(*c))))
       && is_ldc_string(next(next(next(next(*c)))), &y2)
       && is_label(next(next(next(next(next(*c))))), &x2)
       && currentlabels[x2].sources == 1
       && strcmp(y2, "null") == 0) {
        droplabel(x1);
        return replace(c, 6, makeCODEldc_string(y1, NULL));
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
 * iload x
 * ldc 0
 * imul
 * ------------->
 * ldc 0
 *
 * OR
 *
 * iload x
 * ldc 1
 * imul
 * ------------->
 * iload x
 *
 * OR
 *
 * iload x
 * ldc 2
 * imul
 * ------------->
 * iload x
 * dup
 * iadd
 */
int simplify_multiplication_right(CODE** c) {
    int x, k;
    if(is_iload(*c, &x) &&
            is_ldc_int(next(*c), &k) &&
            is_imul(next(next(*c)))) {
        if(k == 0) {
            return replace(c, 3, makeCODEldc_int(0, NULL));
        } else if(k == 1) {
            return replace(c, 3, makeCODEiload(x, NULL));
        } else if(k == 2) {
            return replace(c, 3, makeCODEiload(x, makeCODEdup(makeCODEiadd(NULL))));
        }
        return 0;
    }
    return 0;
}

/*
 * return
 * <some code>
 * X:
 * --------->
 * return
 * X:
 */
int strip_post_return(CODE** c) {
    int x, y;
    if(is_return(*c)
       && !is_label(next(*c), &y)
       && is_label(next(next(*c)), &x)) {
        return replace(c, 3, makeCODEreturn(makeCODElabel(x, NULL)));
    }
    return 0;
}

/*
 * areturn
 * <some code>
 * X:
 * --------->
 * return
 * X:
 */
int strip_post_areturn(CODE** c) {
    int x, y;
    if(is_areturn(*c)
       && !is_label(next(*c), &y)
       && is_label(next(next(*c)), &x)) {
        return replace(c, 3, makeCODEareturn(makeCODElabel(x, NULL)));
    }
    return 0;
}

/*
 * ireturn
 * <some code>
 * X:
 * --------->
 * return
 * X:
 */
int strip_post_ireturn(CODE** c) {
    int x, y;
    if(is_ireturn(*c)
       && !is_label(next(*c), &y)
       && is_label(next(next(*c)), &x)) {
        return replace(c, 3, makeCODEireturn(makeCODElabel(x, NULL)));
    }
    return 0;
}

void init_patterns(void) {
    /*Given optimization*/
    ADD_PATTERN(positive_increment);            /*OK*/
    ADD_PATTERN(simplify_istore);               /*OK*/
    ADD_PATTERN(simplify_astore);               /*OK*/
    ADD_PATTERN(simplify_multiplication);       /*OK*/
    ADD_PATTERN(simplify_division_right);       /*OK*/
    ADD_PATTERN(simplify_subtract_left);        /*OK*/
    ADD_PATTERN(simplify_self_subtract);        /*OK*/
    ADD_PATTERN(simplify_addition);             /*OK*/
    ADD_PATTERN(simplify_branch_1);             /*OK*/
    ADD_PATTERN(simplify_branch_2);             /*OK*/
    ADD_PATTERN(simplify_branch_3);             /*OK*/
    ADD_PATTERN(simplify_branch_4);             /*OK*/
    ADD_PATTERN(simplify_branch_6);             /*OK*/
    ADD_PATTERN(simplify_branch_7);             /*OK*/
    ADD_PATTERN(simplify_branch_8);             /*OK*/
    ADD_PATTERN(simplify_branch_9);             /*OK*/
    /*TODO
     * Duplicate simplify_branch_9 but:
     * ...
     * ifne ..
     * pop
     * */
    /**
     * TODO
     * Create simplify_branch_10 to solve the invoke operand
     * Use swap to work around the invoke
     */
    ADD_PATTERN(simplify_goto_goto);            /*OK*/
    ADD_PATTERN(simplify_ldc_istore);           /*OK*/
    ADD_PATTERN(remove_nop);                    /*OK*/
    ADD_PATTERN(negative_increment);            /*OK*/
    ADD_PATTERN(simplify_putfield);             /*OK*/
    ADD_PATTERN(simplify_swap_1);               /*OK*/
    ADD_PATTERN(simplify_swap_2);               /*OK*/
    ADD_PATTERN(simplify_swap_3);               /*OK*/
    ADD_PATTERN(simplify_swap_4);               /*OK*/
    ADD_PATTERN(simplify_swap_5);               /*OK*/
    ADD_PATTERN(simplify_string);               /*OK*/
    ADD_PATTERN(merge_labels);                  /*OK*/
    ADD_PATTERN(remove_dead_labels);            /*OK*/
    ADD_PATTERN(simplify_multiplication_right); /*OK*/
    ADD_PATTERN(strip_post_return);             /*OK*/
    ADD_PATTERN(strip_post_areturn);            /*OK*/
    ADD_PATTERN(strip_post_ireturn);            /*OK*/
}
