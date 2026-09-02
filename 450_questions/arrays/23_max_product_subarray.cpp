/*
 * QUESTION: Find Maximum Product Subarray
 * Link: https://practice.geeksforgeeks.org/problems/maximum-product-subarray3604/1
 * 
 * Input: arr[] = {6, -3, -10, 0, 2}
 * Output: Max Product = 180 (Subarray is {6, -3, -10})
 */

#include <iostream>
#include <vector>
#include <algorithm>

// Returns the maximum product of a contiguous subarray.
long long maxProductSubarray(const std::vector<int>& arr) {
    if (arr.empty()) return 0;
    
    long long max_prod = arr[0];
    long long min_prod = arr[0];
    long long ans = arr[0];
    
    for (size_t i = 1; i < arr.size(); i++) {
        long long val = arr[i];
        
        // If we encounter a negative number, maximum product becomes minimum product
        // and minimum product becomes maximum product when multiplied.
        if (val < 0) {
            std::swap(max_prod, min_prod);
        }
        
        max_prod = std::max(val, max_prod * val);
        min_prod = std::min(val, min_prod * val);
        
        ans = std::max(ans, max_prod);
    }
    
    return ans;
}

/*
 * DRY RUN (arr = {6, -3, -10, 0, 2}):
 * Initial: max_prod = 6, min_prod = 6, ans = 6
 * 
 * | Step | i | val | Swap? | max_prod Calculation          | min_prod Calculation          | ans Updated        |
 * | :--- | :-| :-- | :---- | :---------------------------- | :---------------------------- | :----------------- |
 * | Init | - | -   | -     | 6                             | 6                             | 6                  |
 * | 1    | 1 | -3  | Yes   | swap -> max=-3, min=6         |                               |                    |
 * |      |   |     |       | max( -3, -3 * -3)             | min( -3, 6 * -3)              |                    |
 * |      |   |     |       | max(-3, 9) = 9? No!           | min(-3, -18) = -18            |                    |
 * |      |   |     |       | Wait, swap makes max=6, min=6 |                               |                    |
 * |      |   |     |       | after swap: max=-3*6=-18, etc | Let's trace carefully:        |                    |
 * |      |   |     |       | max_prod = max(-3, -3 * 6)    | min_prod = min(-3, -3 * 6)    |                    |
 * |      |   |     |       | max(-3, -18) = -3             | min(-3, -18) = -18            | max(6, -3) = 6     |
 * | 2    | 2 | -10 | Yes   | swap -> max=-18, min=-3       |                               |                    |
 * |      |   |     |       | max(-10, -10 * -18) = 180     | min(-10, -10 * -3) = -10      | max(6, 180) = 180  |
 * | 3    | 3 | 0   | No    | max(0, 0 * 180) = 0           | min(0, 0 * -10) = 0           | max(180, 0) = 180  |
 * | 4    | 4 | 2   | No    | max(2, 2 * 0) = 2             | min(2, 2 * 0) = 0             | max(180, 2) = 180  |
 * 
 * Max Product: 180
 * 
 * MEMORIZATION / RECALL SCENARIO:
 * Think of it as riding a roller coaster of values. 
 * Usually, a positive number keeps you high (max product) and a negative sinks you (min product). 
 * But a loop-the-loop (multiplying by another negative) flips the floor and the ceiling. 
 * So, whenever you see a negative sign, swap your floor (min) and ceiling (max) before multiplying.
 * 
 * 1-MINUTE QUICK REVISION:
 * - Initialize `max_prod = arr[0]`, `min_prod = arr[0]`, and `ans = arr[0]`.
 * - For each element from index 1 to n-1:
 *   - If the element is negative, `swap(max_prod, min_prod)`.
 *   - Update `max_prod = max(element, max_prod * element)`.
 *   - Update `min_prod = min(element, min_prod * element)`.
 *   - Update `ans = max(ans, max_prod)`.
 * - Time Complexity: O(N)
 * - Space Complexity: O(1)
 */
