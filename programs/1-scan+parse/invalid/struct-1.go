// cannot use nested struct declaration within the same struct

package main

var t struct {
    a, b int
    type nested struct {
        c int
        d string
    }
    e nested  // nested struct declaration used within same struct
}

func main() {

}