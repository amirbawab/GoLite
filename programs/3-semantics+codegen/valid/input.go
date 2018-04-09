//~a string
//~1
//~2
//~2

package main

func main() {
    var a int
    a = 1
    var b int = 1
    b = 2
    var c = 1
    c = 2
    {
        var a string = "a string"
        println(a)
    }
    println(a)
    println(b)
    println(c)
}
