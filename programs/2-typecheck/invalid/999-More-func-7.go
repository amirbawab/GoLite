// cannot use type a to return
package main

type a int

func test(a a) int {
	return a
}

func main() {
	test(0)
}