// right operand of + must be a string or numeric
package main

func main() {
    type a struct { a int }
    var test a

    println('test' + test)
}