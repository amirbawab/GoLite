//~2
//~2
//~3
//~3
package main

type PersonB struct {
    age int
}

type PersonA struct {
    age int
    friend []PersonB
};

func main() {
    // Create objects
    var a PersonA
    var b PersonA
    var c PersonB

    // Initialize slice in a
    a.friend = append(a.friend, c);
    a.friend[0].age = 1;

    // Slice content must point to the same elements after an =
    b = a
    b.friend[0].age = 2;
    println(a.friend[0].age)
    println(b.friend[0].age)

    // Now slice content must point to different elements
    b.friend = append(b.friend, c);
    b.friend[0].age = 3;
    println(a.friend[0].age)
    println(b.friend[0].age)
}
