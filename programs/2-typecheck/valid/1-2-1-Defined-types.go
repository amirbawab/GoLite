// Display symbol table on this
package main

type num int
type natural num

type floats []float64
type naturals []natural

// To be shadowed
func INT() {}

func main() {

    // Shadow function
    type INT int
}

