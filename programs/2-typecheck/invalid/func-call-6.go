cannot use test (type func() int) as type int in argument to test2
package main

func test() int {
    return 0
}

func test2(a int) {
    return 0
}

func main() {
    test2(test)
}