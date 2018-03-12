// Package short declarations
package main

func main() {
    // 1. All expressions on the right hand side are well-typed
    a, b, c, d, e := 1, 2.3, true, 'r', "string"

    // 2. At least one variable on the left-hand side
    // is not declared in the current scope
    // 3. Variables already declared in the current scope
    // are assigned expressions of the same type
    a, b, c, d, e, f := 2, 3.4, false, 'R', "STRING", "new"
}
