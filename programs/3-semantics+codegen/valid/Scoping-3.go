//~3
//~2
//~1
package main

var a int = 1

func main() {
	var a int = 1
	{
		var int = 2
		{
			var int = 3
			println(int)
		}
		println(int)
	}
	println(a)
}
