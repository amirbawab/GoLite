// no condition on the else branch!

package main

func main() {
    if(1 == 2) {
        println("test")
    } else(1 == 3) { // conditioning the else is invalid
        println("test2")
    }
}