import java.util.*;
public class slide_window{

    static class Pair implements Comparable<Pair>{
        int val;
        int idx;

        public Pair(int val, int idx){
            this.val = val;
            this.idx = idx;
        }
        @Override
        public int compareTo(Pair p2){
            //for accending 
            //return this.val - p2.val;

            //for decendint
            return p2.val - this.val;
        }

    }
    public static void main(String args[]){
        int arr[] = {1,3,-1,-3,5,3,6,7};
        int k = 3; // window size
        int res[] = new int[arr.length-k+1];
        //System.out.println(res.length);
        PriorityQueue<Pair> pq = new PriorityQueue<>();

        //first window
        for(int i=0; i<k; i++){
            pq.add(new Pair(arr[i],i));
        }
        //adding the first number
        res[0] = pq.peek().val;

        for(int i = k; i<arr.length; i++){
            while(pq.size()>0 && pq.peek().val <= (i-k)){
                pq.remove();
            }

            pq.add(new Pair(arr[i],i));
            res[i-k+1] = pq.peek().val;
        }

        //print results
        for(int i =0; i<res.length; i++){
            System.out.print(res[i]+" ");
        }

    }
}

/*
User: Can you help me to understand this question also dry run and please let me understand hwo comparable is also working and give strcutre of priority queue.

GitHub Copilot: Read [](file:///c%3A/Users/lalit.k/lalit/d/dsa/Apna-College-AlphaBatch-DSA-JAVA-main/Heaps_Priority%20Queue/slide_window.java)

Perfect! Let me explain this problem in detail with a dry run.

## Problem Understanding

This is the **Maximum in Sliding Window** problem. You have an array and need to find the maximum element in every sliding window of size `k`.

**Input:** `arr = [1,3,-1,-3,5,3,6,7]`, `k = 3`
**Output:** `[3,3,5,5,6,7]` (maximum in each window)

---

## How `Comparable` Works

`Comparable<Pair>` is an interface that allows objects to be compared and ordered.

```
Comparable<Pair> interface
    ↓
compareTo(Pair p2) method
    ↓
Returns:
  - Negative (< 0): this object is smaller
  - Zero (= 0): objects are equal
  - Positive (> 0): this object is larger
```

In your code:
```java
return p2.val - this.val;  // Descending order (max heap)
```
- If `p2.val > this.val`: result is positive → p2 comes first
- This creates a **Max Heap** (largest element at the top)

---

## Priority Queue Structure

```
PriorityQueue<Pair> pq
    ↓
    ┌─────────────────┐
    │   Max Heap      │
    │   (Tree-based)  │
    └─────────────────┘
    
Each element is a Pair:
    Pair { val: value, idx: index }
    
Heap organizes by compareTo():
- peek() → O(1) get max
- add() → O(log n) insert
- remove() → O(log n) delete
```

---

## Dry Run with Your Input

**Array:** `[1, 3, -1, -3, 5, 3, 6, 7]`, **k = 3**

| Step | Window | Operation | PQ Contents | Max | res |
|------|--------|-----------|-------------|-----|-----|
| **Initialize Window 0** | [1,3,-1] | Add (1,0), (3,1), (-1,2) | (3,1) → (-1,2) → (1,0) | 3 | [3] |
| **i=3** | [3,-1,-3] | Remove idx ≤ 0; Add (-3,3) | (3,1) → (-1,2) → (-3,3) | 3 | [3,3] |
| **i=4** | [-1,-3,5] | Remove idx ≤ 1; Add (5,4) | (5,4) → (-1,2) → (-3,3) | 5 | [3,3,5] |
| **i=5** | [-3,5,3] | Remove idx ≤ 2; Add (3,5) | (5,4) → (3,5) → (-3,3) | 5 | [3,3,5,5] |
| **i=6** | [5,3,6] | Remove idx ≤ 3; Add (6,6) | (6,6) → (5,4) → (3,5) | 6 | [3,3,5,5,6] |
| **i=7** | [3,6,7] | Remove idx ≤ 4; Add (7,7) | (7,7) → (6,6) → (3,5) | 7 | [3,3,5,5,6,7] |

---

## Why This Works

1. **Max Heap** always keeps the largest element at the top
2. **Remove old elements:** `pq.peek().idx <= (i-k)` removes elements outside the window
3. **Add new element:** Each new element from the right side
4. **Get max:** `pq.peek().val` gives the maximum in the current window

**Time Complexity:** O(n log n)  
**Space Complexity:** O(k) for the queue

Does this clarify the concept? Would you like me to trace through any specific step in more detail?
*/