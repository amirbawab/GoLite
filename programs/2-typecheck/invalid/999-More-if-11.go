 // else if expression does not evaluate to bool
package main

func main() {
    if true {
        println("test")
    } else if 1 { // does not resolve to bool
        println("test")
    } else {
        println("test")
    }
}