// Binary expressions
package main

func main() {
    type INT int
    type FLOAT64 float64
    type RUNE rune
    type STRING string
    type BOOL bool

    var a int
    var b float64
    var c rune
    var d string
    var e bool
    var A INT
    var B FLOAT64
    var C RUNE
    var D STRING
    var E BOOL

    // && ||
    // Boolean operands
    e = e && e
    E = E && E
    e = e || e
    E = E || E

    // == !=
    // Comparable operands
    e = a == a
    e = b == b
    e = c == c
    e = d == d
    e = e == e
    e = A == A
    e = B == B
    e = C == C
    e = D == D
    e = E == E

    // < <= > >=
    // Ordered operands
    e = a < a
    e = b < b
    e = c < c
    e = d < d
    e = A < A
    e = B < B
    e = C < C
    e = D < D

    e = a > a
    e = b > b
    e = c > c
    e = d > d
    e = A > A
    e = B > B
    e = C > C
    e = D > D

    e = a <= a
    e = b <= b
    e = c <= c
    e = d <= d
    e = A <= A
    e = B <= B
    e = C <= C
    e = D <= D

    e = a >= a
    e = b >= b
    e = c >= c
    e = d >= d
    e = A >= A
    e = B >= B
    e = C >= C
    e = D >= D

    // +
    // Numeric or string operand
    a = a + a
    b = b + b
    c = c + c
    d = d + d
    A = A + A
    B = B + B
    C = C + C
    D = D + D
    
    // - / *
    a = a - a
    b = b - b
    c = c - c
    A = A - A
    B = B - B
    C = C - C

    a = a / a
    b = b / b
    c = c / c
    A = A / A
    B = B / B
    C = C / C

    a = a * a
    b = b * b
    c = c * c
    A = A * A
    B = B * B
    C = C * C

    // % | & << >> &^ ^
    a = a % a
    A = A % A

    a = a | a
    A = A | A

    a = a & a
    A = A & A

    a = a << a
    A = A << A

    a = a >> a
    A = A >> A

    a = a &^ a
    A = A &^ A

    a = a ^ a
    A = A ^ A
}
