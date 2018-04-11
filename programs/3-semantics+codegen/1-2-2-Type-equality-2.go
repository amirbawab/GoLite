package main

func main() {
    type A int
    var a A
    var b int
    a = b // Incompatible types A and int
}
