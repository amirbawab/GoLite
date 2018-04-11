// invalidField is undefined
package main

type c bool

func main() {
    type a struct { a int; }
    var b a
    var c int = 0
    for b.a = 0; true; b.invalidField++ { // invalid field undefined
        println("test")
    }
}