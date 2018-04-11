//~1 +2.300000e+000 114 true string 1
package main

func main() {
	var a int
	var b [1]float64
	var c [1]rune
	var d bool
	var e string
	var f struct {
		g int
	}

	// 1. All the expressions on the left hand side are well-typed
	// 2. All the expressions on the right hand side are well-typed
	// 3. For every pair of (left value, expression),
	// typeof(vi) = typeof(ei) (no resolving)
	// 4. Left value:
	//    - Variables (non-constant)
	//    - Slice indexing
	//    - Array indexing of an addressable array
	//    - Field selection an addressable struct

	a, b[0], c[0], d, e, f.g = 1, 2.3, 'r', true, "string", 1
	println(a, b[0], c[0], d, e, f.g)
}
