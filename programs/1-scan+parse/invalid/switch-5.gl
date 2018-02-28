// switch initial statement cannot be a blank identifier

package main

func main() {
    var x int = 0
    switch _ {
        case 1, 2, 3,: // dangling ,
            println("is one")
        case 2:
            println("is two")
        default:
            println("is something else")
    }
}