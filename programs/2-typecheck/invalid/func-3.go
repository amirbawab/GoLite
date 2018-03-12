// cannot redefine identifiers within the same scope
package main

func test() {
    var test int = 0 // cannot redeclare test
}

func main() {
    test()
}