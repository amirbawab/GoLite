package main

func main() {
    var a struct{ a int; }
    a.a = 1.2; // int != float64
}
