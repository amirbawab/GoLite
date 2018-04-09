//~97
//~97
//~a
//~a
package main

func main() {
    type STRING string
    type INT int
    var a int = 97
    var b INT = INT(a)
    var c STRING = STRING(b)
    var d string = string(c)
    println(a)
    println(b)
    println(c)
    println(d)
}
