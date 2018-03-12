// A print statement type checks if all its expressions 
// are well-typed and resolve to a base type 
// (int, float64, bool, string, rune)
package main

func main() {
    type INT int
    type FLOAT64 float64
    type BOOL bool
    type STRING string
    type RUNE rune

    var a int
    var b float64
    var c bool
    var d string
    var e rune

    var A INT
    var B FLOAT64
    var C BOOL
    var D STRING
    var E RUNE

    // Is basic type
    print(a, b, d, e)
    println(a, b, d, e)

    // Resolve to basic type
    println(A, B, D, E)
    print(A, B, D, E)
}
