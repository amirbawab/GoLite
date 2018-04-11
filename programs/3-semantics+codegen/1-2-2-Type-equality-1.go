package main

func main() {
    type A int
    var a A
    var b int
    b = a // Incompatible int and A
}
