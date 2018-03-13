// println expression should symtable pass
package main

type a struct { a int; }

func main() {
    var test a
    println(test.nonExisting) // non existing field does not exist
}