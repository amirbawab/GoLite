// a used as non-bool value
package main

type a bool

func main() {
    for a := 5; a; a++ { // a is used a numeric
        println("test")
    }
}