// selector primary operator only applied to struct
package main

type a int

func main() {
    a.x = 0 // a is not a struct
    println("finished")
}