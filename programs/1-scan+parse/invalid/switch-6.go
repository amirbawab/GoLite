// switch case cannot be a blank identifier

package main

func main() {
    var x int = 0
    switch  {
        case _: // cannot be a blank identifier
            println("is one")
        default:
            println("is something else")
    }
}