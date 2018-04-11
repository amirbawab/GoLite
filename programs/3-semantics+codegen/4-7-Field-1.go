package main

var a struct{a int;}
func main() {
    a.b = 123; // Undefined member
}
