// invalid nonExistingType not defined for func return type
package main

func test() nonExistingType {
    println("test")
    return
}

func main() {
    test()
}
