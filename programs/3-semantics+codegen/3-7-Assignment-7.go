package main

func main() {
    var a struct { a int; }
    a.b = 123 // member not found
}
