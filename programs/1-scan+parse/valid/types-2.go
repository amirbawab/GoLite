package main;


func main() {
	type (
		Point struct{ x, y float64; }  // Point and struct{ x, y float64 } are different types
		polar Point                   // polar and Point denote different types
	)

	type TreeNode struct {
		left, right TreeNode
		value Comparable
	}
}
