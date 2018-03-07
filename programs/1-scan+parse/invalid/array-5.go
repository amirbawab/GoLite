// invalid array access

package main;

func main() {
    var x [99]int;
    y := x[]; // invalid access
}