// Indexing
package main

func main() {

    type INT int
    var a []int
    var b [10]int
    var c int
    var d INT

    // Expr is well-typed and resolves to []T or [N]T
    // Index is well-typed and resolves to int
    a[c] = a[c]
    b[d] = b[d]
}
