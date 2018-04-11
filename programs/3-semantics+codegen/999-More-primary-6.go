// returned type is not an array

package main

func foo() {
    return 1
}

func main() {
    println(foo()[0]) // foo is not an array
}