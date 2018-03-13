 // c does not exists within else scope
package main

func main() {
    if true {
        var c int = 0
    } else {
        println(c)
    }
}