package main

type A int
var a A
func main() {
    type A float64
    var b A
    a = b // A != A (shadowed)
}

