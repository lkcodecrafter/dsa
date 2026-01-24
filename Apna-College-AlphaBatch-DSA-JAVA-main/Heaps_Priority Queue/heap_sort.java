
public class heap_sort {

    public static void heapify(int arr[],int i, int size){
        int left = 2*i+1;
        int right = 2*i+2;
        int maxIdx = i;

        if(left < size && arr[left] > arr[maxIdx]){
            maxIdx = left;
        }

        if(right < size && arr[right] > arr[maxIdx]){
            maxIdx = right;
        }

        if(maxIdx != i){
            //swap
            int temp = arr[i];
            arr[i] = arr[maxIdx];
            arr[maxIdx] = temp;

            heapify(arr,maxIdx,size);
        }
    }

    public static void heapSort(int arr[]){
        //step 1 - build maxHeap
        int n = arr.length;
        for(int i = n/2; i>=0; i--){ // i from n/2 because from last filled level
            heapify(arr,i,n);
        }

        //step 2 - push largest at end
        for(int i = n-1; i>0; i--){
            //swap (largest-first with last)
            int temp = arr[0];
            arr[0] = arr[i];
            arr[i] = temp;

            heapify(arr,0,i);
        }
    }
    public static void main(String args[]){
        int arr[] = {1,2,4,5,3};

        heapSort(arr);
        int n = arr.length;
        //print 
        for(int i = 0; i<n; i++){
            System.out.print(arr[i]+" ");
        }
    }
    
}
/*
 

Short explanation
- heapify(arr, i, size) ensures the subtree rooted at index i satisfies the max-heap property (parent >= children), assuming the subtrees of i are already max-heaps.
- It:
  1. computes left = 2*i+1 and right = 2*i+2,
  2. finds the largest of arr[i], arr[left], arr[right] (only if indices < size),
  3. if a child is larger, swaps arr[i] with the largest child and recursively heapifies that child index.
- The `size` parameter limits the active heap (used during sorting as the heap shrinks).
- heapify time: O(log n) in worst case. Heapsort overall: O(n log n) time, O(1) extra space, not stable.

Why build heap from i = n/2 down to 0
- Indices > n/2 - 1 are leaves (no children). Starting at floor(n/2)-1 (or n/2 in integer loop that includes 0) ensures you call heapify on every internal node so the entire array becomes a max-heap.

Dry run on arr = {1, 2, 4, 5, 3} (0-based indices shown)

Initial:
- arr = [1, 2, 4, 5, 3], n = 5

Build max-heap (for i = n/2 down to 0)
- i = 2: left=5,right=6 (out of range) → no change  
  arr = [1, 2, 4, 5, 3]

- i = 1: left=3 (5), right=4 (3). Max of {arr[1]=2,5,3} is arr[3]=5 → swap index1 & 3  
  after swap: [1, 5, 4, 2, 3]  
  heapify at index 3: no children → done

- i = 0: left=1 (5), right=2 (4). Max of {1,5,4} is arr[1]=5 → swap 0 & 1  
  after swap: [5, 1, 4, 2, 3]  
  heapify at index 1: left=3 (2), right=4 (3). Max of {1,2,3} is arr[4]=3 → swap 1 & 4  
  after swap: [5, 3, 4, 2, 1]  
  heapify at index 4: no children → done

Max-heap built:
- arr = [5, 3, 4, 2, 1]

Sorting phase (swap root with last, reduce size, heapify root)

- i = 4: swap arr[0] & arr[4] → [1, 3, 4, 2, 5]  
  heapify(root, size=4): left=1 (3), right=2 (4) → max is index2 (4) → swap 0 & 2  
  after heapify: [4, 3, 1, 2, 5]

- i = 3: swap arr[0] & arr[3] → [2, 3, 1, 4, 5]  
  heapify(root, size=3): left=1 (3), right=2 (1) → max is index1 → swap 0 & 1  
  after heapify: [3, 2, 1, 4, 5]

- i = 2: swap arr[0] & arr[2] → [1, 2, 3, 4, 5]  
  heapify(root, size=2): left=1 (2) → swap 0 & 1  
  after heapify: [2, 1, 3, 4, 5]

- i = 1: swap arr[0] & arr[1] → [1, 2, 3, 4, 5]  
  heapify(root, size=1): nothing to do

Final sorted array (ascending):
- [1, 2, 3, 4, 5]

Notes / common pitfalls
- Building the heap is usually implemented with for (int i = n/2 - 1; i >= 0; i--) — your loop uses n/2 but still works because it includes the same internal nodes when i decrements to 0.
- heapify is called with a shrinking size during the sort so elements after index size-1 are the sorted suffix and are not considered part of the heap.
- Heapsort sorts in-place but is not stable (equal elements may reorder).

If you want, I can show the exact sequence of function calls and recursion tree for each heapify call.

*/