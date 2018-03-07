// types cannot be redefined

package main

func test() {
    println("test")
}

func main() {
    var test = "test" // test redeclared in this block
}