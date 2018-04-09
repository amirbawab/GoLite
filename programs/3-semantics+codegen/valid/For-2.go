//~0
//~1
//~2
//~3
//~4
//~5
//~6
//~7
//~8
//~9

package main
 
func bubblesort(a []int) {
    for itemCount := 10 - 1; ; itemCount-- {
        hasChanged := false
        for index := 0; index < itemCount; index++ {
            if a[index] > a[index+1] {
                a[index], a[index+1] = a[index+1], a[index]
                hasChanged = true
            }
        }
        if hasChanged == false {
            break
        }
    }
}

func main() {
    var list []int
    list = append(list, 9)
    list = append(list, 8)
    list = append(list, 7)
    list = append(list, 6)
    list = append(list, 5)
    list = append(list, 4)
    list = append(list, 3)
    list = append(list, 2)
    list = append(list, 1)
    list = append(list, 0)
    bubblesort(list)
    for i:=0; i < 10; i++ {
        println(list[i]);
    }
}
