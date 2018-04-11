package main

func main() {
    type A int
    var a A
    a, b := 1, false // index 0 should not resolve to int
}
