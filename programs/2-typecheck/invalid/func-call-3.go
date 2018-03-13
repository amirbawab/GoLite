// breaks rule 1 of function checkParams()
package main

func test(int a) {
    return a
}

type b struct { a int; }

func main() {
    var c b
    test(c) // breaks rule 1
}
