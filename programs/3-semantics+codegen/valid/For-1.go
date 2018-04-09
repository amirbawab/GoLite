//~1111111111
//~22222222222222222222
//~33333333333

package main

func main() {
    

    // Three-part for loop
    for for_1 := 0; for_1 < 10; for_1++ {
        print(1);
    }
    println();

    // While loop
    var for_2 int = 0;
    for for_2 < 20 {
        print(2);
        for_2++;
    }
    println();

    // Infinite loop
    var for_3 int = 0;
    for {
        print(3);
        if for_3 == 10 {
            break;
        }
        for_3++;
    }
    println();
}
