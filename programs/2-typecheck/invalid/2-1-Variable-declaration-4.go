package main

type A int
var a A
var b = a
func main() {
    b = 123 // Incompatible A and int
}
