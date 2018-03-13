package main

type c bool

func main() {
    var a c = false
    for b := 0; a; b++ { // c is not an expression
        println("valid")
    }
}