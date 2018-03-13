// a does not exist within function scope
package main

func main() {
    for a:= 0; a < 5; a++ {
        println("test")
    }

    println(a) // undefined a
}