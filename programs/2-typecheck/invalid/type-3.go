// type cannot be recursive
package main

type a int
type int a

func main() {
    println("test")
}