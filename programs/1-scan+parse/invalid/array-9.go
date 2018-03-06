// invalid array identifier to access
package main

var a[10] int;

func main() {
    [2]a // expected expression
}