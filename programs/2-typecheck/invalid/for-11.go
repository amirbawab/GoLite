// a does not exist within function scope

func main() {
    for a:= 0; a < 5; a++ {
        println("test")
    }

    println(a) // undefined a
}