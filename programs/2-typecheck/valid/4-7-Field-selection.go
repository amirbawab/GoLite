// Field selection
package main

func main() {
    
    type A struct { a int; }
    type B struct { a []A; }
    type C struct { a B; }
    type D struct { a []C; }
    type E struct { a D; }
    var e E

    // Expr is well-typed
    // Resolves to a struct that has a valid field name
    e.a.a[0].a.a[0].a = 123

    // Resolve when indexing
    type F int
    type G []F
    type H G
    type I []H
    type J I
    var j J
    var f F
    j[0][0] = f

    // Resolve when indexing
    type K []int
    type L K
    type M []L
    type N M
    type O []N
    var o O
    o[0][0][0] = 1
}
