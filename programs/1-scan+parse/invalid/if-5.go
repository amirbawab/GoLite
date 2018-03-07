// c/java-like single statement after if expression are not allowed in golang

package main

func main() {
    if(1 == 2) // not allowed, requires brackets
        println("testing")
}