// Return statement
package main

func f1() {

    // Well-type if the enclosing function has no return type
    return;

    // Should be evaluated even after a return
    f1();
}

func f2(a int) int {
    
    // Well-typed if its expression is well-typed and the type
    // of this expression is the same as the return type of the
    // enclosing function
    return 1 + 2;

    // Should be evaluated even after a return expr
    f2(1 + 2);
}
