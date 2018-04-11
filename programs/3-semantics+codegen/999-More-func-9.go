// cannot redeclare a in the same block
package main

type a int
func a() int {
    return 0
}

func main() {
    a()
}