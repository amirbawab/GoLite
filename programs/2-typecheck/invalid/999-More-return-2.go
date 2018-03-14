// type check within return statement
package main

func test() int {
    return 3.1416 // return expected to return int instead got float
}

func main() {
    test()
}