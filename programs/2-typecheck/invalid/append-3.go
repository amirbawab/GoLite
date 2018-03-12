// more than 2 arguments to slices
package main

var x []int;
func main() {
    x = append(x, 0.2, x, x); // 2nd argument not same type as slice
};