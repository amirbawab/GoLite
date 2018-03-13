// print builtin function expects base type only
package main

type a struct { test int }

func main() {
    var test a
    print(test) // print expects base types
}