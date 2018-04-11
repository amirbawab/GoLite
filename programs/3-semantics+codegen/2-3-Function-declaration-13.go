package main

func hello() int {
    if true {
        return 1
    } else if true {
        // Missing return in else if
    } else {
        return 3
    }
}
