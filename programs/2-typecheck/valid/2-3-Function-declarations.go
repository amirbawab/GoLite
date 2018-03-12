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

// Hidden return
func f7() int { 
    if true {
        return 1;
    } else {
        return 0;
    }
}
