//~5 4 3 2 1
package main

func main() {
	// 1. All expressions on the right hand side are well-typed
	a, b, c, d, e := 1, 2, 3, 4, 5
	a, b, c, d, e = e, d, c, b, a

	println(a, b, c, d, e)
}
