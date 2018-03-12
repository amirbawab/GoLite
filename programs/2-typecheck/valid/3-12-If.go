// If statement
package main

func main() {
    type BOOL bool

    var b bool
    var B BOOL

    // An if statmenet type checks if:
    //  - Its expression is well-typed and resolves to type bool
    //  - The statemnts type check
    if b { b:=1.2; }
    if B { b:=1.2; }

    // Init type check
    // Init can shadow variables declared in the same scope
    if B:=1.2; b { b:=1.2; }
    if b:=1.2; B { b:=1.2; }
}
