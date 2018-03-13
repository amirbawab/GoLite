// invalid field within return statement
type a struct { a int }

func test() a {
    var t a
    return t.nonExisting // non existing field
}

func main() {
    test()
}