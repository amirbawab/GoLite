//~Before sorting:
//~10,9,8,7,6,5,4,3,2,1,
//~After sorting:
//~1,2,3,4,5,6,7,8,9,10,
package main

var N int = 10
 
// Insertion sort
func sort(nums []int) {
    for i := 1; i < N; i++ {
        v := nums[i]
        j := i - 1
        for j >= 0 && nums[j] > v {
            nums[j+1] = nums[j]
            j = j - 1
        }
        nums[j+1] = v
    }
}
 
func main() {
    var nums []int
    // Initilize array
    for i:=0; i < N; i++ {
        nums = append(nums, N - i);
    }
    // Print array before sorting
    println("Before sorting:")
    for i:=0; i < N; i++ {
        print(nums[i],",")
    }
    sort(nums)
    // Print array after sorting
    println("\nAfter sorting:");
    for i:=0; i < N; i++ {
        print(nums[i],",")
    }
}

