// Unary expressions
package main

func main() {
    type ints []int
    type floats []float64
    type runes []rune
    type bools []bool
    type INT int
    type FLOAT64 float64
    type RUNE rune
    type BOOL bool

    var a int
    var b float64
    var c rune
    var d ints
    var e floats
    var f runes
    var g bool
    var h bools
    var A INT
    var B FLOAT64
    var C RUNE
    var G BOOL

    // Unary plus must resolve to a numeric 
    // type (int, float64, rune)
    a = +a
    b = +b
    c = +c
    d[0] = +d[0]
    e[0] = +e[0]
    f[0] = +f[0]
    A = +A
    B = +B
    C = +C

    // Unary minus must resolve to a numeric 
    // type (int, float64, rune)
    a = -a
    b = -b
    c = -c
    d[0] = -d[0]
    e[0] = -e[0]
    f[0] = -f[0]
    A = -A
    B = -B
    C = -C

    // Unary logical negation must resolve to a bool
    g = !g
    G = !G
    h[0] = !h[0]

    // Bitwise negtion expr must resolve to an interger
    // type (int, rune)
    a = ^a
    A = ^A
    c = ^c
    C = ^C
    d[0] = ^d[0]
    f[0] = ^f[0]
}
