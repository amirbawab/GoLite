// foo() used as value
package main

func foo() {
    return 1
}

func main() {
    println((foo())[0]) // foo is used as a value
}