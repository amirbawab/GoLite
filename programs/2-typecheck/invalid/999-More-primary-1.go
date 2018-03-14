// symbol exists but is not called
package main

func test() int {
    return 0
}

func main() {
    println(test) // test expects to be called
}