// Function declarations
package main

// No params
func f1() {}

// One param
func f2(a int) {}

// Two params
func f3(a int, b int) {}

// Two params
func f4(a, b int) {}

// Return int
func f5() int { return 1; }

// Return void
func f6() { return; }

// End with if
func f7() int { 
    if true {
        return 1;
    } else if true {
        return 2;
    } else {
        return 0;
    }
}

// End with for
func f8() int {
    for{}
}

// End with switch
func f9() int {
    switch {
    case true:
        return 1;
    default:
        return 2;
    }
}
