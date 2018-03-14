package main

func hello() int {
    if true {
        // missing return in if
    } else {
        return 2
    }
}
