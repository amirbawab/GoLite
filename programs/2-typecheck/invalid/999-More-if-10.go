 // c does not exists within else scope
package main

func main() {
    if true {
        println(c)
    } else {
        var c int = 0
        println(c)
    }
}