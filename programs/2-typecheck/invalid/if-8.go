// b does not resolve to boolean
package main

func main() {
    type a struct { a int }
    var b a
    if b { // b does not resolve to boolean

    }
}
