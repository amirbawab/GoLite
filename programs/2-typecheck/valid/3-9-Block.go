// Block
package main

func main() {
    var a int = 1
    {
        // Shado outer a
        var a float64 = 1.2
    }
    {
        // Shadow outer a
        var a bool = true
    }
}
