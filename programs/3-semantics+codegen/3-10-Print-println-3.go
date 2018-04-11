package main

func main() {
    type A [1]int
    var a A
    print(a) // must resolve to base type
}
