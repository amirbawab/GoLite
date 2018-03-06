// array access must contain an expression

package main;

func main() {
    var x [99]int;
    x[] = 0; // invalid array access
}