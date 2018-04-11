package main

func main() {
    type A []int
    var a A
    print(a) // Must resolve to a base type
}
