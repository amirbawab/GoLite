// Shadow a variable in nested blocks
package main

var a int = 1;
func main() {
    var a int = 1;
    {
        var int = 1;
        {
            var int = 1;
        }
    }
}
