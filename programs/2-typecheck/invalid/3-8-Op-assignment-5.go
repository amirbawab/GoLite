package main

func main() {
    type A float64
    var a A
    a %= a // Must resolve to an int
}
