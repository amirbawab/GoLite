// Append
package main

func main() {
    var a []int
    var b [][]int

    // e1 is well-typed and resolves to []T
    // e2 is well-typed and resolves to T
    var c []int = append(a, a[0])
    var d int = append(b[a[0]], b[a[0]][b[0][0]])[0]
}
