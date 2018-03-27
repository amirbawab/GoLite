//~x is one
//~x is two
//~x is something else

package main

func main() {
    var x int = 1;

    // Switch form 1
    switch {
    case x == 1:
        println("x is one");
    case x == 2:
        println("x is two");
    default:
        println("x is something else");
    }

    // Switch form 2
    switch x := x+1; x {
    case 1:
        println("x is one");
    case 2:
        println("x is two");
    default:
        println("x is something else");
    }

    // Switch form 3
    switch x := x+2; x {
    case 1, 2:
        println("x is one or two");
    default:
        println("x is something else");
    }
}
