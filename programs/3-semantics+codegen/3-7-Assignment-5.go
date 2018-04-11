package main

func f1() int {
    return 1
}

func hello() {
    f1() = 123 // cannot be a function call
}
