//~true
//~true
//~true
//~true
//~true
//~true
//~true
//~true
//~true
//~true
//~true
//~truetruetruetruetruetruetruetruefalse
//~false
//~false
package main

func one() int {
    return 1
}

func two() int {
    return 2
}

func and(left, right bool) bool {
    // Test return
    return left && right || true
}

func or(left, right bool) bool {
    return left || right && true
}

func boolToInt(val bool) int {
    if val {
        return 1
    } else {
        return 0
    }
}

func main() {
    // Test variable
    var expr1 bool = one() == 1 && two() == 2
    var expr2 bool = one() == 1 || two() == 2

    // Test function call
    var expr5 bool = and(one() == 1 && true, two() == 2 || true || false)
    var expr6 bool = or(one() == 1 && true, two() == 2 || true || false)

    // Test short declaration
    expr3, expr4 := one() == 1 && two() == 2, one() == 1 || two() == 2

    // Test assignment
    expr5 = one() == 1 && two() == 2
    expr6 = one() == 1 || two() == 2
    expr5, expr6 = one() == 1 && two() == 2, one() == 1 || two() == 2

    // Test if
    if one() == 1 && two() == 2 || true {
        println(true)
    }

    // Test else if
    if one() == 1 && two() == 2 && false {
        println(false)
    } else if one() == 1 && two() == 2 || true {
        println(true)
    }

    // Test for
    for i, t:=0, one() == 1 && two() == 2; one() == 1 && two() == 2 && i == 1; i++ {
        println(true)
        println(t)
    }

    // Test switch
    switch one() == 1 && two() == 2 && true {
        case one() == 1 && two() == 2 && true:
            println(true)
        case one() == 1 || two() == 2 || true:
    }

    // Test print 
    println(expr1)
    println(expr2)
    println(expr3)
    println(expr4)
    println(expr5)
    println(expr6)
    println(one() == 1 && two() == 2 && true)
    println(one() == 1 || two() == 2 || true)

    // Test print
    print(expr1)
    print(expr2)
    print(expr3)
    print(expr4)
    print(expr5)
    print(expr6)
    print(one() == 1 && two() == 2 && true)
    print(one() == 1 || two() == 2 || true)

    // Test index
    var expr7 [10]bool
    println(expr7[boolToInt(one() == 1 && two() == 2 && true)])
    println(expr7[boolToInt(one() == boolToInt(one() == 1 && two() == 2 && true) && two() == 2 && true)])

    // Test append
    var expr8 []bool
    expr8 = append(expr8, expr7[boolToInt(one() == boolToInt(one() == 1 && two() == 2 && true) && two() == 2 && true)])

    // Test parenthesis
    println((expr7)[(boolToInt)((one()) == (boolToInt)(((one)() == 1 && two() == 2 && true)) && (two() == 2 && true))])

}
