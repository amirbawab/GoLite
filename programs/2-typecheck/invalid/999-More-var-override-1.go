// types cannot be redefined

 package main

 func main() {
     type test struct { a int; }
     var test = "test" // test redeclared in this block (in same scope)
 }
