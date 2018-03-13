// type definition does not exist within else scope
package main

func main() {
    if true {
        println("test")
    } else if { // does not resolve to bool
        type a struct { a int }
        println("test")
    } else {
        var test a // undefined a
        println("test")
    }
}