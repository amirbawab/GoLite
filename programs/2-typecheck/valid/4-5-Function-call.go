// Function calls
package main

type INT int

func f1() int {
    return 1
}

func f2() float64 {
    return 1.2
}

func f3() bool {
    return true
}

func f4() string {
    return "string"
}

func f5() rune {
    return 'a'
}

func f6() {}

func f7() INT {
    var a INT
    return a
}

func f8() [][]int {
    var a [][]int
    return a
}

func f9() struct { a []int; } {
    var a struct { a []int; }
    return a
}

func f10(a int) int {
    return 1
}

func main() {
    var a int = f1()
    var b float64 = f2()
    var c bool = f3()
    var d string = f4()
    var e rune = f5()
    f6()
    var f INT = f7()
    var g []int = f8()[0]
    var h int = f9().a[0];
    var i int = f10(f1());
}
