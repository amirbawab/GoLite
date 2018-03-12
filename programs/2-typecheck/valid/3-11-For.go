// Fo loops
package main

func main() {
    type BOOL bool

    var b bool
    var B BOOL

    // No expression
    for {
        // Shadow b
        b := 1.2
    }

    // A while loop type checks if:
    //  - Its expression is well-typed and resolves to type bool
    //  - The statemnts type check
    for b { b:=1.2; }
    for B { b:=1.2; }

    // Init type check
    // Init can shadow variables declared in the same scope
    for B:=1.2; b; B++ { b:=1.2; }
    for b:=1.2; B; b++ { b:=1.2; }
}
