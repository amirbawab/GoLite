// print expression should symtable pass
package main

type a struct { a int; }

func main() {
    var test a
    print(test.nonExisting) // non existing field does not exist
}