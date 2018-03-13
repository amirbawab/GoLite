// invalidField is undefined
package main

type c bool

func main() {
    type a struct { a int }
    var b a
    var c int = 0
    for b.invalidField = 0; true; c++ { // invalid field undefined
        println("test")
    }
}