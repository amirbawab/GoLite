// Type casting
package main

func main() {
    // Type-cast is well-typed if: type(expr)
    // type resolves to a base type int, float64, bool, rune, string
    // Expr is well-typed and has a type that can be cast to type:
    //  - type and expr resolves to numeric types
    //  - type and expr both resolve to numeric types
    //  - type resolves to a string type and expr resolves
    //    to an integer type (rune or int)
    type base10 int
    type number base10
    var a int
    var b base10
    var c number

    var d int = int(c)
    var e int = int(b)
    var f int = int(a)
    var g base10 = base10(c)
    var h base10 = base10(b)
    var i base10 = base10(a)
    var j number = number(c)
    var k number = number(b)
    var l number = number(a)

    var m string = string(123)
    var n string = string("string")
}
