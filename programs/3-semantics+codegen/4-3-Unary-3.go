package main

type A bool
var a A

func f1() A {
    return a
}
func main() {
    a := -f1() // Should resolve to numeric
}
