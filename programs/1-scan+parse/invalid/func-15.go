// function call does not accept blank identifier

package main

func main() {
	test(_, _) // does not accept blank identifier
}

func test(string s, ss int) int {
	return 0
}
