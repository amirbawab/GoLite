package main

func main() {
    y := 1
    switch y {
        case 1, 2, 3:
            println("test")
        case 2:
            println("test 2")
        default:
            println("default test case")
    }
}