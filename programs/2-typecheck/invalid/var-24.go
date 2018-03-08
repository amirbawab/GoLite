// Access wrong value
package main
func main() {
    var a struct { b int; }
    x := a
    x.c = 123;
}
