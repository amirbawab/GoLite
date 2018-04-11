package main

func main() {
    type A int
    type B []A
    var a []A
    var b B
    b = a // Incompatible B and []A
}
