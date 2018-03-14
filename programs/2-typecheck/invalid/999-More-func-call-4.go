// breaks rule 3 of function call checkParams()
package main

func test(a string) {
    return a
}

type a struct { d int; }

func main() {
    test(a) // breaks rule 3
}