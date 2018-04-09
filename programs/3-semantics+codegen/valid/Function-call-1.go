//~3 3 5
//~4
package main

var a [10]int;
func k() struct{} {
    	var x struct{};
	return x;
}

func inc(k struct{}) int {
    a[0]++;
    return a[0]
}

func main() {
    println(a[0], a[0] + a[(((inc)))(k())], inc(k()) + inc(k()));
    println(inc(k()))
}

