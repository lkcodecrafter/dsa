import java.util.*;
public class largest_subArray_sum_0 {

/*


## What the code does

This code finds the length of the largest subarray with sum 0 in the given array.  
It uses a HashMap to store the first occurrence of each prefix sum.

### Step-by-step explanation

1. Iterate through the array, maintaining a running sum (`sum`).
2. For each element:
   - Add it to `sum`.
   - If `sum` is already in the map, it means the subarray between the previous index (where this sum was first seen) and the current index has a sum of 0.
   - Update `len` to the maximum length found so far.
   - If `sum` is not in the map, store its index.
3. Print the maximum length found.

## Dry run with your array

Given: `arr = {15, -2, 2, -8, 1, 7, 10, 23}`

| i  | arr[i] | sum | map (sum:index)         | len | Explanation                                 |
|----|--------|-----|-------------------------|-----|---------------------------------------------|
| 0  | 15     | 15  | {15:0}                  | 0   | First time sum=15, store index 0            |
| 1  | -2     | 13  | {15:0, 13:1}            | 0   | First time sum=13, store index 1            |
| 2  | 2      | 15  | {15:0, 13:1}            | 2   | sum=15 seen before at 0, len=max(0,2-0)=2   |
| 3  | -8     | 7   | {15:0, 13:1, 7:3}       | 2   | First time sum=7, store index 3             |
| 4  | 1      | 8   | {15:0, 13:1, 7:3, 8:4}  | 2   | First time sum=8, store index 4             |
| 5  | 7      | 15  | {15:0, 13:1, 7:3, 8:4}  | 5   | sum=15 seen before at 0, len=max(2,5-0)=5   |
| 6  | 10     | 25  | {15:0, 13:1, 7:3, 8:4, 25:6}| 5 | First time sum=25, store index 6            |
| 7  | 23     | 48  | {15:0, 13:1, 7:3, 8:4, 25:6, 48:7}| 5 | First time sum=48, store index 7        |

**Result:**  
The largest subarray with sum 0 has length 5 (from index 1 to 5: `-2, 2, -8, 1, 7`).

---

If you need a more detailed step-by-step or have questions about any part, let me know!

*/

    public static void main(String args[]){
        int arr[] = {15,-2,2,-8,1,7,10,23};

        HashMap<Integer,Integer> map = new HashMap<>();

        int sum =0;
        int len =0;

        for(int i =0; i<arr.length; i++){
            sum+=arr[i];
            if(map.containsKey(sum)){
                //means the sum is repeating so value of max Subarray can increase
               len =  Math.max(len,i-map.get(sum));//here i is minused because we want only the between after the last zero sum subarray and till the elment now we are at

            }else{
                map.put(sum,i);
            }
        }

        System.out.println("Max subarray with sum  0 is "+len);
    }
}
