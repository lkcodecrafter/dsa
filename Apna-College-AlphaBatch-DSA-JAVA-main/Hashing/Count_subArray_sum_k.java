import java.util.*;
public class Count_subArray_sum_k {

/*


## What does the code do?

This code counts the number of subarrays in the array `arr` whose sum is exactly `k`.  
It uses a HashMap to efficiently keep track of prefix sums and their frequencies.

### Key Concepts

- **Prefix Sum:** The sum of elements from the start of the array up to the current index.
- **HashMap:** Stores how many times each prefix sum has occurred.

### How does it work?

1. Initialize a HashMap `map` to store prefix sums and their counts. Start with `map.put(0,1)` to handle subarrays starting from index 0.
2. Iterate through the array, maintaining a running sum (`sum`).
3. For each element:
   - Check if `(sum - k)` exists in the map. If yes, it means there is a subarray ending at the current index with sum `k`.
   - Add the count of `(sum - k)` to the answer.
   - Update the map with the current `sum`.

---

## Dry Run

Given:
- `arr = {10, 2, -2, -20, 10}`
- `k = -10`

Let's walk through each step:

| i | arr[i] | sum  | sum-k | map (before)         | ans (before) | map (after)          | ans (after) |
|---|--------|------|-------|----------------------|--------------|----------------------|-------------|
| 0 | 10     | 10   | 0     | {0=1}                | 0            | {0=1, 10=1}          | 0           |
| 1 | 2      | 12   | 2     | {0=1, 10=1}          | 0            | {0=1, 10=1, 12=1}    | 0           |
| 2 | -2     | 10   | 20    | {0=1, 10=1, 12=1}    | 0            | {0=1, 10=2, 12=1}    | 0           |
| 3 | -20    | -10  | 0     | {0=1, 10=2, 12=1}    | 0            | {0=1, 10=2, 12=1, -10=1} | 1       |
| 4 | 10     | 0    | 10    | {0=1, 10=2, 12=1, -10=1} | 1      | {0=2, 10=2, 12=1, -10=1} | 3       |

### Step-by-step explanation:

- At i=0: sum=10, sum-k=0. map has 0, so ans += 1 (but only after i=3). Update map: 10 appears once.
- At i=1: sum=12, sum-k=2. map has no 2. Update map: 12 appears once.
- At i=2: sum=10, sum-k=20. map has no 20. Update map: 10 appears twice.
- At i=3: sum=-10, sum-k=0. map has 0, so ans += 1 (ans=1). Update map: -10 appears once.
- At i=4: sum=0, sum-k=10. map has 10 (count=2), so ans += 2 (ans=3). Update map: 0 appears twice.

**Final Output:**  
`System.out.println(ans);` prints `3`.

---

## Summary

- The code efficiently counts subarrays with sum `k` using prefix sums and a HashMap.
- For the given input, there are 3 subarrays whose sum is -10.

If you want a more detailed breakdown of which subarrays those are, let me know!

*/    

    public static void main(String args[]){

        int arr[] = {10,2,-2,-20,10};
        int k = -10;

        HashMap<Integer, Integer> map = new HashMap<>();
        //we need to put (0,1) in map for some corner cases
        map.put(0,1);


        int sum =0;
        int ans = 0;

        for(int i =0; i<arr.length; i++){
            sum += arr[i];
            if(map.containsKey(sum - k)){
                ans+=map.get(sum-k);
            }else{
                map.put(sum,map.getOrDefault(sum,0)+1);
            }
        }

        System.out.println(ans);
    }
}
