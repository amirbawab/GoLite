// Undefined variable in another scope
package main

func main() {
    {
        var a int = 1
    }
    {
        a = 1
    }
}
