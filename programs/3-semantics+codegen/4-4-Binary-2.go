package main

func main() {
    type A bool
    var a A
    var b bool = a || a // bool != A
}
