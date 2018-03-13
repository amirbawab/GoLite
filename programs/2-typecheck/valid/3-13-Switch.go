// Switch statement
package main

func main() {

    var a int
    var b bool

    // A switch statement with an expression type checks if:
    //  - init type checks
    //  - expr is well-typed
    //  - e1, e2, ..., en are well-typed and have the same
    //    type as expr
    //  - statement under the different alternatives type check
    switch a {
        case 1:
        case 2, 3, 4:
        default:
    }

    // Init can shadow variable in the same scope
    switch a:=true; a {
        case true:
        case false:
        default:
    }

    // Switch without an expression type checksi if
    //  - init type checks
    //  - e1, e2, ..., en are well-typed and have type bool 
    //    (no resolve)
    //  - statement under the different alternatives type check
    switch {
        case true:
        case false:
        case b:
        default:
    }
    
}
