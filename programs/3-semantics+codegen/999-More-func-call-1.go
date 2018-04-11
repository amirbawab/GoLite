// invalid number of parameters for function call
package main

func foo(int a) {
    print(a)
}

func main() {
    foo() // invalid number of parameters
}