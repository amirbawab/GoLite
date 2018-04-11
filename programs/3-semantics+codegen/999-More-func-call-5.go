// nonExisting type makes sure symbol table pass called for parameters
package main

func test(c nonExisting) { // non existing type
    return "test"
}

func main() {
    test(2)
}