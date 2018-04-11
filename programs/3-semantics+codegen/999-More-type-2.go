// cannot redeclare same type in block
package main

type a int
type a float64 // type already declared

func main() {
    println("test")
}