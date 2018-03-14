// symbol table phase within for-loop block
package main

func main() {
    for a:= 0; a < 5; a++ {
        var test typeDoesNotExist
        test.nonExisting = false
    }
}