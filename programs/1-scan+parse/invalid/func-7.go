// function declaration should not have a trailing comma

package main

func main() {
    foo("a", "b", "c")
}

func foo(a,b,c, string) { // trailing comma
    println(a)
    println(b)
    println(c)
}