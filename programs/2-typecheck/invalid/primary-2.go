// selector can only be applied to struct types
package main

func test() {
    return 1
}

func main() {
    println(test.attr1) // must be a struct in order to use selected
}