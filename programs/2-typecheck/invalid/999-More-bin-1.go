// test is not a compatible type (is a function)
package main

func test() {
    println("test")
}

func main() {
    println(test + "test")
}