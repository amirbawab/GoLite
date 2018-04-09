//~0
//~0
//~+5.000000e-001
//~0
//~+1.500000e+000
//~1
//~+2.500000e+000
//~2
//~+3.500000e+000
//~3
//~+4.500000e+000
//~4
//~0
//~0
//~0
//~0
//~0
package main

type num int
type natural num

type floats []float64
type naturals [10]natural

func main() {
    var v_num num
    var v_natural natural
    var v_floats floats
    var v_naturals naturals

    // Add data to array/slice
    for i:=0; i < 5; i++ {
        v_floats = append(v_floats, .5 + float64(i))
        v_naturals[i] = natural(i);
    }

    println(v_num)
    println(v_natural)
    for i:=0; i < 10; i++ {
        if i < 5 {
            println(v_floats[i])
        }
        println(v_naturals[i])
    }
}

