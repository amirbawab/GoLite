// +//+ is an invalid operator

package main

func main() {
    var i int = 0;
    i+//+ // checking if only ignoring comments causes + // + to be interpreted as ++
}