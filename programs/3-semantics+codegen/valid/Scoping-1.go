//~1
//~1
//~1
//~11
//~1
//~1
//~22
//~2
//~2
//~33
//~3
//~3
//~44
//~4
//~4
package main

// Initial declaration for variable x
var x int = 1

func main() {
    println(x)

    // Re-declare x inside a function
    var x int = x;
    println(x);
    {
        // Re-declare x inside a block
        var x int = x;
        println(x);

        // Re-declare x in a for loop
        for x := x; x < 5; x++ {
            print(x)

            // Re-declare x in an if statement
            if x := x; true {
                println(x);

                // Re-declare x in a switch statement
                switch x := x; {
                    case true:
                        // Re-declare x in a short declaration
                        x := x;
                        println(x);
                }

                // Re-declare x in a sibling switch statement
                switch x := x; {
                    case true:
                        // Re-declare x in a short declaration
                        x := x;
                        println(x);
                }
            }
        }
    }
}
