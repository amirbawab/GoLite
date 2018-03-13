// println builtin function expects base type only
package main

type a struct { test int }

func main() {
    var test a
    println(test) // print expects base types
}