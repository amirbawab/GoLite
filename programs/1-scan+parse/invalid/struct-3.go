// assigning values to a struct is done using =
package main

type z struct {
    x,y float64
}

var y z
func main() {
    y.x := 0.2 // assigning values using a := is invalid
}