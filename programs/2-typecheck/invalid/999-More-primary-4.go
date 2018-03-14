// non existing field in struct
package main

type a struct { b int; }

func main() {
    var test a
    a.nonExisting = 0

    println("finished")
}