// return statement may not return ++ or --

package main

func main() { // forgot func keyword
	println("test")
}

func test(string s, ss int) int { // invalid parameters
	i := 0
	return i++ // apparently not possible in golang!
}
