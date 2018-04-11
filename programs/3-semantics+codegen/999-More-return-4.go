// cannot return functions
package main

func testing() {
    return "test"
}

func test() {
    return testing // testing is a type function
}

func main() {
    test()
}