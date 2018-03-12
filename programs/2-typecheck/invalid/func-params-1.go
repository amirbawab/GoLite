// a is already declared within block

package main

func a() {
    return 0
}

func test(a int) int {
    return a
}

func main() {
    test(0)
}