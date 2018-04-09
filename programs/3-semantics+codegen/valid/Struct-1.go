//~123
//~124

package main

func main() {
    var a struct {a int;}
    var b struct {a int;}
    a.a = 123;
    b = a;
    b.a += 1;
    println(a.a)
    println(b.a)
}
