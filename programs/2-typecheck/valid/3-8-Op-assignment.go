// Assignment
package main

func main() {
    var a int
    var b []float64
    var c []rune
    var e string
    var f struct { g int; }

    // 1. All the expressions on the left hand side are well-typed
    // 2. All the expressions on the right hand side are well-typed
    // 3. typeof(v) = typeof(expr)
    // 4. Left value:
    //    - Variables (non-constant)
    //    - Slice indexing
    //    - Array indexing of an addressable array
    //    - Field selection an addressable struct

    a += 1
    b[0] += 2.3
    c[0] += 'r'
    e += "string"
    f.g += 1
}
