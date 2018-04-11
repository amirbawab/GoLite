// function body does not typecheck
package main

type a int
func test(b a) int {
    var a int = 'r' + 0
    return "a" + a
}

func main() {
	test(0)
}