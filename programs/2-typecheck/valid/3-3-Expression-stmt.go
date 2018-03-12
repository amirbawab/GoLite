// Expression statement is well-typed if its expression child
// is well-typed.
package main

func f(a int) {
    f(1 + 2)
    (f(1 + 2))
    ((f(1 + 2)))
}
