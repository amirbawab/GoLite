// Symbol table should start with:
// --------------------------
// ID       CATEGORY    TYPE
// true     constant    bool
// false    constant    bool
// int      type        int
// float64  type        float64
// rune     type        rune
// bool     type        bool
// string   type        string

package main

func main() {
    var a bool = true
    var b bool = false
    var c int = 123
    var d float64 = 1.2
    var e rune = 'a'
    var f string = "string"
}
