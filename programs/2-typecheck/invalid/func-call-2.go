// incompatible parameters in function call
package main

func foo(int a) {
    print a
}

func main() {
    foo("test")
}