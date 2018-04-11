package main

type A bool
var a A
func main() {
    switch {
    case a: // Cannot resolve to bool
    }
}
