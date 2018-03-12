// Type declarations
package main

func main() {

    // Create a new type
    type A int

    // Use the new type
    var a A

    {
        // Showdown type A
        type A float64

        // Use shadowed type
        var a A
    }
}
