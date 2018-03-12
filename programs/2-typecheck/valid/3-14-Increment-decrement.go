// Increment and decrement statement
package main

func main() {
    type INT int
    type STRUCT struct { a int; }
    
    var a int
    var b INT
    var c STRUCT
    var d []int
    var e float64
    var f rune

    // Expression is well-typed
    // Resolves to an numeric base type )int, float64, rune)
    a++
    b++
    c.a++
    d[0]++
    e++
    f++
}
