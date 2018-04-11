package main

type A int
func hello() int {
    var a A
    return a // Should not resolve
} 
