//~11
package main

var a int = 10;
func incA() int {
    a++
    return a
}
func main() {
    switch incA() {
    case 1:
    case 2:
    case 3:
    }
    print(a)
}
