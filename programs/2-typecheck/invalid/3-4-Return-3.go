package main

func hello() int {
    return 1
    hello(1, 2)  // must still be evaluated after a return
    return 2
}
