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

/* iload x
 * ldc 0
 * if_icmpeq
 * --------->
 * iload x
 * if_eq
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

/* aload x
 * aconst_null
 * if_acmpeq
 * --------->
 * aload x
 * ifnull
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
    if (is_ldc_int(next(*c), &x2)
        && x2 == 0
        && is_goto(next(next(*c)), &x3)
        && is_label(next(next(next(*c))), &x4)
        && is_ldc_int(next(next(next(next(*c)))), &x5)
        && x5 == 1
        && is_label(next(next(next(next(next(*c))))), &x6)
        && x3 == x6
        && currentlabels[x6].sources == 1
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
        if(is_ifeq(*c, &x1)) {
            droplabel(x1);
            droplabel(x3);
            return replace(c, 7, makeCODEifne(x7, NULL));
        }
        if(is_ifne(*c, &x1)) {
            droplabel(x1);
            droplabel(x3);
            return replace(c, 7, makeCODEifeq(x7, NULL));
        }
        if(is_ifnull(*c, &x1)) {
            droplabel(x1);
            droplabel(x3);
            return replace(c, 7, makeCODEifnonnull(x7, NULL));
        }
        if(is_ifnonnull(*c, &x1)) {
            droplabel(x1);
            droplabel(x3);
            return replace(c, 7, makeCODEifnull(x7, NULL));
        }
    }
    return 0;
}

/**
 * ifeq true        <-- reduce label
 * goto else
 * true:
 * ---------->
 * ifne else
 */
int simplify_branch_4(CODE **c) {
    int x1, x2, x3;
    if(is_goto(next(*c), &x2)
       && is_label(next(next(*c)), &x3)) {
        if(is_if_acmpeq(*c, &x1)) {
            droplabel(x1);
            return replace(c, 3, makeCODEif_acmpne(x2, NULL));
        }
        if(is_if_acmpne(*c, &x1)) {
            droplabel(x1);
            return replace(c, 3, makeCODEif_acmpeq(x2, NULL));
        }
        if(is_if_icmpeq(*c, &x1)) {
            droplabel(x1);
            return replace(c, 3, makeCODEif_icmpne(x2, NULL));
        }
        if(is_if_icmpne(*c, &x1)) {
            droplabel(x1);
            return replace(c, 3, makeCODEif_icmpeq(x2, NULL));
        }
        if(is_if_icmplt(*c, &x1)) {
            droplabel(x1);
            return replace(c, 3, makeCODEif_icmpge(x2, NULL));
        }
        if(is_if_icmple(*c, &x1)) {
            droplabel(x1);
            return replace(c, 3, makeCODEif_icmpgt(x2, NULL));
        }
        if(is_if_icmpgt(*c, &x1)) {
            droplabel(x1);
            return replace(c, 3, makeCODEif_icmple(x2, NULL));
        }
        if(is_if_icmpge(*c, &x1)) {
            droplabel(x1);
            return replace(c, 3, makeCODEif_icmplt(x2, NULL));
        }
        if(is_ifeq(*c, &x1)) {
            droplabel(x1);
            return replace(c, 3, makeCODEifne(x2, NULL));
        }
        if(is_ifne(*c, &x1)) {
            droplabel(x1);
            return replace(c, 3, makeCODEifeq(x2, NULL));
        }
        if(is_ifnull(*c, &x1)) {
            droplabel(x1);
            return replace(c, 3, makeCODEifnonnull(x2, NULL));
        }
        if(is_ifnonnull(*c, &x1)) {
            droplabel(x1);
            return replace(c, 3, makeCODEifnull(x2, NULL));
        }
    }
    return 0;
}

/**
 * if(true) and while(true) are removed
 * if(false) and while(false) are removed with their body
 */
int simplify_branch_5(CODE **c) {
    int x1,x2,x3;
    if(is_ldc_int(*c, &x1)) {

        /*Eliminate true conditions*/
        if((is_ifeq(next(*c), &x2) && x1 != 0)
           || (is_ifne(next(*c), &x2) && x1 == 0)) {
            return replace(c, 2, NULL);
        }

        /*Delete dead branch*/
        if((is_ifeq(next(*c), &x2) && x1 == 0)
           || (is_ifne(next(*c), &x2) && x1 != 0)) {
            CODE* nextCode = *c;
            int pc = 0;
            while((nextCode = next(nextCode))) {
                pc++;
                if(is_label(nextCode, &x3) && x2 == x3) {
                    return replace(c, pc, NULL);
                }
            }
        }
    }
    return 0;
}

/**
 * acsont_null
 * if_acmpeq
 * ---------->
 * ifnull
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
 * iconst_0
 * if_icmpeq
 * ---------->
 * ifeq
 */
int simplify_branch_7(CODE **c) {
    int x1, x2;
    if(is_ldc_int(*c, &x1) && x1 == 0) {
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
 * if_acmpeq true_2     <-- reduce label
 * iconst_0
 * goto stop_3          <-- reduce label
 * true_2:
 * iconst_1
 * stop_3:
 * dup
 * ifeq|ifne
 * ------------>
 * ???????
 */
int simplify_branch_8(CODE **c) {
    int x1,x2,x3,x4,x5,x6,x7;
    if (is_if(c, &x1)
        && is_ldc_int(next(*c), &x2)
        && x2 == 0
        && is_goto(next(next(*c)), &x3)
        && is_label(next(next(next(*c))), &x4)
        && is_ldc_int(next(next(next(next(*c)))), &x5)
        && x5 == 1
        && is_label(next(next(next(next(next(*c))))), &x6)
        && x3 == x6
        && currentlabels[x6].sources != 1
        && is_dup(next(next(next(next(next(next(*c)))))))) {
        if(is_ifeq(next(next(next(next(next(next(next(*c))))))), &x7) || is_ifne(next(next(next(next(next(next(next(*c))))))), &x7)) {
            /* TODO */
        }
    }
    return 0;
}

/**
 * dup
 * ifne A
 * pop
 * ...........
 * A:
 * ifeq | ifne
 * ------------>
 * Follow the if maybe?
 */
int simplify_branch_9(CODE **c) {
    /* TODO */
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
            if(is_ifeq(*c,&x1)) {
                return replace(c, 1, makeCODEifeq(x2, NULL));
            }
            if(is_ifne(*c,&x1)) {
                return replace(c, 1, makeCODEifne(x2, NULL));
            }
            if(is_if_acmpeq(*c, &x1)) {
                return replace(c, 1, makeCODEif_acmpeq(x2, NULL));
            }
            if(is_if_acmpne(*c, &x1)) {
                return replace(c, 1, makeCODEif_acmpne(x2, NULL));
            }
            if(is_ifnull(*c, &x1)) {
                return replace(c, 1, makeCODEifnull(x2, NULL));
            }
            if(is_ifnonnull(*c, &x1)) {
                return replace(c, 1, makeCODEifnonnull(x2, NULL));
            }
            if(is_if_icmpeq(*c, &x1)){
                return replace(c, 1, makeCODEif_icmpeq(x2, NULL));
            }
            if(is_if_icmpgt(*c, &x1)) {
                return replace(c, 1, makeCODEif_icmpgt(x2, NULL));
            }
            if(is_if_icmplt(*c, &x1)) {
                return replace(c, 1, makeCODEif_icmplt(x2, NULL));
            }
            if(is_if_icmple(*c, &x1)) {
                return replace(c, 1, makeCODEif_icmple(x2, NULL));
            }
            if(is_if_icmpge(*c, &x1)) {
                return replace(c, 1, makeCODEif_icmpge(x2, NULL));
            }
            if(is_if_icmpne(*c, &x1)) {
                return replace(c, 1, makeCODEif_icmpne(x2, NULL));
            }
        }
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
 * ldc | iload | aload
 * ldc | iload | aload
 * swap
 * ----->
 * ldc | iload | aload
 * ldc | iload | aload
 */
int simplify_swap_1(CODE **c) {
    int x1, x2;
    char* y1, *y2;
    if(is_swap(next(next(*c)))) {
        if(is_aload(*c, &x1) && is_aload(next(*c), &x2)) {
            return replace(c, 3, makeCODEaload(x2, makeCODEaload(x1, NULL)));
        }
        if(is_iload(*c, &x1) && is_iload(next(*c), &x2)) {
            return replace(c, 3, makeCODEiload(x2, makeCODEiload(x1, NULL)));
        }
        if(is_iload(*c, &x1) && is_aload(next(*c), &x2)) {
            return replace(c, 3, makeCODEaload(x2, makeCODEiload(x1, NULL)));
        }
        if(is_aload(*c, &x1) && is_iload(next(*c), &x2)) {
            return replace(c, 3, makeCODEiload(x2, makeCODEaload(x1, NULL)));
        }
        if(is_ldc_int(*c, &x1) && is_iload(next(*c), &x2)) {
            return replace(c, 3, makeCODEiload(x2, makeCODEldc_int(x1, NULL)));
        }
        if(is_iload(*c, &x1) && is_ldc_int(next(*c), &x2)) {
            return replace(c, 3, makeCODEldc_int(x2, makeCODEiload(x1, NULL)));
        }
        if(is_ldc_int(*c, &x1) && is_aload(next(*c), &x2)) {
            return replace(c, 3, makeCODEaload(x2, makeCODEldc_int(x1, NULL)));
        }
        if(is_aload(*c, &x1) && is_ldc_int(next(*c), &x2)) {
            return replace(c, 3, makeCODEldc_int(x2, makeCODEaload(x1, NULL)));
        }
        if(is_ldc_string(*c, &y1) && is_iload(next(*c), &x2)) {
            return replace(c, 3, makeCODEiload(x2, makeCODEldc_string(y1, NULL)));
        }
        if(is_iload(*c, &x1) && is_ldc_string(next(*c), &y2)) {
            return replace(c, 3, makeCODEldc_string(y2, makeCODEiload(x1, NULL)));
        }
        if(is_ldc_string(*c, &y1) && is_aload(next(*c), &x2)) {
            return replace(c, 3, makeCODEaload(x2, makeCODEldc_string(y1, NULL)));
        }
        if(is_aload(*c, &x1) && is_ldc_string(next(*c), &y2)) {
            return replace(c, 3, makeCODEldc_string(y2, makeCODEaload(x1, NULL)));
        }
        if(is_aconst_null(*c) && is_aload(next(*c), &x1)) {
            return replace(c, 3, makeCODEaload(x1, makeCODEaconst_null(NULL)));
        }
        if(is_aload(*c, &x1) && is_aconst_null(next(*c))) {
            return replace(c, 3, makeCODEaconst_null(makeCODEaload(x1, NULL)));
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
 * dup
 * getfield
 */
int simplify_swap_3(CODE **c) {
    int x1, x2;
    char *y1;
    if(is_aload(*c, &x1)
       && is_getfield(next(*c), &y1)
       && is_aload(next(next(*c)), &x2)
       && is_swap(next(next(next(*c))))
       && x1 == x2) {
        return replace(c, 4, makeCODEaload(x1, makeCODEdup(makeCODEgetfield(y1, NULL))));
    }
    return 0;
}

/**
 * new
 * dup
 * ldc | aload | iload
 * invokenonvirtual
 * aload_0
 * swap
 * putfield
 * ----------->
 * aload_0
 * new
 * dup
 * ldc | aload | iload
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
        if(is_ldc_int(next(next(*c)), &x2)) {
            return replace(c, 7, makeCODEaload(x1, makeCODEnew(y1, makeCODEdup(makeCODEldc_int(x2, makeCODEinvokenonvirtual(y2, makeCODEputfield(y3, NULL)))))));
        }
        if(is_ldc_string(next(next(*c)), &y4)) {
            return replace(c, 7, makeCODEaload(x1, makeCODEnew(y1, makeCODEdup(makeCODEldc_string(y4, makeCODEinvokenonvirtual(y2, makeCODEputfield(y3, NULL)))))));
        }
        if(is_iload(next(next(*c)), &x2)) {
            return replace(c, 7, makeCODEaload(x1, makeCODEnew(y1, makeCODEdup(makeCODEiload(x2, makeCODEinvokenonvirtual(y2, makeCODEputfield(y3, NULL)))))));
        }
        if(is_aload(next(next(*c)), &x2)) {
            return replace(c, 7, makeCODEaload(x1, makeCODEnew(y1, makeCODEdup(makeCODEaload(x2, makeCODEinvokenonvirtual(y2, makeCODEputfield(y3, NULL)))))));
        }
    }
    return 0;
}

/**
 * new
 * dup
 * ldc | aload | iload
 * ldc | aload | iload
 * invokenonvirtual
 * aload_0
 * swap
 * putfield
 * ----------->
 * aload_0
 * new
 * dup
 * ldc | aload | iload
 * ldc | aload | iload
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
        if(is_ldc_int(next(next(*c)), &x2) && is_ldc_int(next(next(next(*c))), &x3)) {
            return replace(c, 8, makeCODEaload(x1, makeCODEnew(y1, makeCODEdup(makeCODEldc_int(x2, makeCODEldc_int(x3, makeCODEinvokenonvirtual(y2, makeCODEputfield(y3, NULL))))))));
        }
        if(is_ldc_string(next(next(*c)), &y4) && is_ldc_string(next(next(next(*c))), &y5)) {
            return replace(c, 8, makeCODEaload(x1, makeCODEnew(y1, makeCODEdup(makeCODEldc_string(y4, makeCODEldc_string(y5, makeCODEinvokenonvirtual(y2, makeCODEputfield(y3, NULL))))))));
        }
        if(is_iload(next(next(*c)), &x2) && is_iload(next(next(next(*c))), &x3)) {
            return replace(c, 8, makeCODEaload(x1, makeCODEnew(y1, makeCODEdup(makeCODEiload(x2, makeCODEiload(x3, makeCODEinvokenonvirtual(y2, makeCODEputfield(y3, NULL))))))));
        }
        if(is_aload(next(next(*c)), &x2) && is_aload(next(next(next(*c))), &x3)) {
            return replace(c, 8, makeCODEaload(x1, makeCODEnew(y1, makeCODEdup(makeCODEaload(x2, makeCODEaload(x3, makeCODEinvokenonvirtual(y2, makeCODEputfield(y3, NULL))))))));
        }
        if(is_ldc_int(next(next(*c)), &x2) && is_ldc_string(next(next(next(*c))), &y4)) {
            return replace(c, 8, makeCODEaload(x1, makeCODEnew(y1, makeCODEdup(makeCODEldc_int(x2, makeCODEldc_string(y4, makeCODEinvokenonvirtual(y2, makeCODEputfield(y3, NULL))))))));
        }
        if(is_ldc_int(next(next(*c)), &x2) && is_iload(next(next(next(*c))), &x3)) {
            return replace(c, 8, makeCODEaload(x1, makeCODEnew(y1, makeCODEdup(makeCODEldc_int(x2, makeCODEiload(x3, makeCODEinvokenonvirtual(y2, makeCODEputfield(y3, NULL))))))));
        }
        if(is_ldc_int(next(next(*c)), &x2) && is_aload(next(next(next(*c))), &x3)) {
            return replace(c, 8, makeCODEaload(x1, makeCODEnew(y1, makeCODEdup(makeCODEldc_int(x2, makeCODEaload(x3, makeCODEinvokenonvirtual(y2, makeCODEputfield(y3, NULL))))))));
        }
        if(is_ldc_string(next(next(*c)), &y4) && is_ldc_int(next(next(next(*c))), &x2)) {
            return replace(c, 8, makeCODEaload(x1, makeCODEnew(y1, makeCODEdup(makeCODEldc_string(y4, makeCODEldc_int(x2, makeCODEinvokenonvirtual(y2, makeCODEputfield(y3, NULL))))))));
        }
        if(is_ldc_string(next(next(*c)), &y4) && is_iload(next(next(next(*c))), &x2)) {
            return replace(c, 8, makeCODEaload(x1, makeCODEnew(y1, makeCODEdup(makeCODEldc_string(y4, makeCODEiload(x2, makeCODEinvokenonvirtual(y2, makeCODEputfield(y3, NULL))))))));
        }
        if(is_ldc_string(next(next(*c)), &y4) && is_aload(next(next(next(*c))), &x2)) {
            return replace(c, 8, makeCODEaload(x1, makeCODEnew(y1, makeCODEdup(makeCODEldc_string(y4, makeCODEaload(x2, makeCODEinvokenonvirtual(y2, makeCODEputfield(y3, NULL))))))));
        }
        if(is_iload(next(next(*c)), &x2) && is_ldc_int(next(next(next(*c))), &x3)) {
            return replace(c, 8, makeCODEaload(x1, makeCODEnew(y1, makeCODEdup(makeCODEiload(x2, makeCODEldc_int(x3, makeCODEinvokenonvirtual(y2, makeCODEputfield(y3, NULL))))))));
        }
        if(is_iload(next(next(*c)), &x2) && is_ldc_string(next(next(next(*c))), &y4)) {
            return replace(c, 8, makeCODEaload(x1, makeCODEnew(y1, makeCODEdup(makeCODEiload(x2, makeCODEldc_string(y4, makeCODEinvokenonvirtual(y2, makeCODEputfield(y3, NULL))))))));
        }
        if(is_iload(next(next(*c)), &x2) && is_aload(next(next(next(*c))), &x3)) {
            return replace(c, 8, makeCODEaload(x1, makeCODEnew(y1, makeCODEdup(makeCODEiload(x2, makeCODEaload(x3, makeCODEinvokenonvirtual(y2, makeCODEputfield(y3, NULL))))))));
        }
        if(is_aload(next(next(*c)), &x2) && is_ldc_int(next(next(next(*c))), &x3)) {
            return replace(c, 8, makeCODEaload(x1, makeCODEnew(y1, makeCODEdup(makeCODEaload(x2, makeCODEldc_int(x3, makeCODEinvokenonvirtual(y2, makeCODEputfield(y3, NULL))))))));
        }
        if(is_aload(next(next(*c)), &x2) && is_ldc_string(next(next(next(*c))), &y4)) {
            return replace(c, 8, makeCODEaload(x1, makeCODEnew(y1, makeCODEdup(makeCODEaload(x2, makeCODEldc_string(y4, makeCODEinvokenonvirtual(y2, makeCODEputfield(y3, NULL))))))));
        }
        if(is_aload(next(next(*c)), &x2) && is_iload(next(next(next(*c))), &x3)) {
            return replace(c, 8, makeCODEaload(x1, makeCODEnew(y1, makeCODEdup(makeCODEaload(x2, makeCODEiload(x3, makeCODEinvokenonvirtual(y2, makeCODEputfield(y3, NULL))))))));
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

void init_patterns(void) {
    /*Given optimization*/
    ADD_PATTERN(positive_increment);
    ADD_PATTERN(simplify_istore);
    ADD_PATTERN(simplify_astore);
    ADD_PATTERN(simplify_multiplication);
    ADD_PATTERN(simplify_division_right);
    ADD_PATTERN(simplify_subtract_left);
    ADD_PATTERN(simplify_self_subtract);
    ADD_PATTERN(simplify_addition);
    ADD_PATTERN(simplify_branch_1);
    ADD_PATTERN(simplify_branch_2);
    ADD_PATTERN(simplify_branch_3);
    ADD_PATTERN(simplify_branch_4);
    /*ADD_PATTERN(simplify_branch_5);*/ /*Works? Need to be tested further*/
    ADD_PATTERN(simplify_branch_6);
    ADD_PATTERN(simplify_branch_7);
    ADD_PATTERN(simplify_branch_8);
    ADD_PATTERN(simplify_branch_9);
    ADD_PATTERN(simplify_goto_goto);
    ADD_PATTERN(simplify_ldc_store);
    ADD_PATTERN(remove_nop);
    ADD_PATTERN(negative_increment); /*Removing this pattern reduces the generated byte code?!*/
    ADD_PATTERN(simplify_putfield);
    ADD_PATTERN(simplify_swap_1);
    ADD_PATTERN(simplify_swap_2);
    ADD_PATTERN(simplify_swap_3);
    ADD_PATTERN(simplify_swap_4);
    ADD_PATTERN(simplify_swap_5);
    ADD_PATTERN(simplify_string);
    ADD_PATTERN(merge_labels);
    ADD_PATTERN(remove_dead_labels);

    ADD_PATTERN(simplify_multiplication_right);
}
