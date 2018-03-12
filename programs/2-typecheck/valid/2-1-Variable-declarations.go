// Variable declarations
package main

func main() {

    // Add 'a' to the symbol table, so we an refer to it
    var a int
    a = 1

    // Expr must be well-typed
    // Add 'b' to the symbol table
    var b int = 1
    b = 2

    // Expr must be well-typed
    // Add 'c' to the symbol table
    // Type of variable becomes the type of the expr
    var c = 1
    c = 2

    {
        // Shadow 'a'
        var a string = "now it is a string"
    }
}
