// Struct testing
package main;

// An empty struct.
type a struct {}

// A struct with 6 fields.
type b struct {
	x, y int;
	u float32;
	_ float32;  // padding
	A []int;
}
