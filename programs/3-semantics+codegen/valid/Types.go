//~1
//~+2.000000e+000
//~true
//~97
//~GoLite
//~1
//~+2.000000e+000
//~true
//~97
//~GoLite
//~Person # 0 > age:  10 > name:  James
//~Person # 1 > age:  11 > name:  Samantha
//~Person # 2 > age:  12 > name:  Karen
//~Person # 3 > age:  13 > name:  James
//~Person # 4 > age:  14 > name:  Samantha
//~Person # 5 > age:  15 > name:  Karen
//~Person # 6 > age:  16 > name:  James
//~Person # 7 > age:  17 > name:  Samantha
//~Person # 8 > age:  18 > name:  Karen
//~Person # 9 > age:  19 > name:  James
//~Person # 10 > age:  0 > name:  

package main

func main() {

    // Custom types
    type INT int
    type FLOAT64 float64
    type BOOL bool
    type RUNE rune
    type STRING string

    // Variable set 1
    var a int = 1
    var b float64 = 2.0
    var c bool = true
    var d rune = 'a'
    var e string = "GoLite"

    // Variable set 2
    var A INT = INT(1)
    var B FLOAT64 = FLOAT64(2.0)
    var C BOOL = BOOL(true)
    var D RUNE = RUNE('a')
    var E STRING = STRING("GoLite")

    // Create custom type: Person
    type Person struct {
        age int
        name string
    }

    // Array of Person
    var people [11]Person

    // Initialize the first 10 people only
    // last one has default values
    for i:=0; i < 10; i++ {
        people[i].age = 10 + i;
        if i % 3 == 0 {
            people[i].name = "James";
        } else if i % 3 == 1 {
            people[i].name = "Samantha";
        } else if i % 3 == 2 {
            people[i].name = "Karen";
        }
    }

    // Print variable set 1
    println(a)
    println(b)
    println(c)
    println(d)
    println(e)

    // Print variable set 2
    println(A)
    println(B)
    println(C)
    println(D)
    println(E)

    // Print people
    for i := 0; i < 11; i++ {
        println("Person #", i, "> age: ", people[i].age, "> name: ", people[i].name)
    }
}
