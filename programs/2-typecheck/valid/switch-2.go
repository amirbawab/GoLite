// Sibling scope of switch case declaring same variable
package main

func main() {
    switch {
        case 1:
            var a int = 1;
        case 2:
            var a int = 1;
    }
}
