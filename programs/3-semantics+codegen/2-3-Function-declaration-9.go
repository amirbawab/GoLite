package main

type A int
func hello() A {
    return 1 // Should not resolve
}
