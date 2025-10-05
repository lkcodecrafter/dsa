import java.util.*;

class Solution{
 
 /*
 ### Approach: HashMap + Max Heap

#### Steps
1. **Count Frequencies**
   - Use `HashMap<Integer,Integer>` to store `element → frequency`.
   
2. **Store in Max Heap**
   - Create `PriorityQueue<Pair>` sorted by frequency descending `(a,b) -> b.val - a.val`.
   
3. **Extract k Elements**
   - Poll the heap `k` times and store the keys in result array.
 */   

 class Pair{
    int key;
    int val;

        public Pair(int k, int v) {
            key =k;
            val =v;
        }
 }
    public int[] topKFrequent(int[] nums, int k) {
        Map<Integer,Integer>mp = new HashMap<>();
        int[]res = new int[k];
        for(int i=0;i<nums.length;i++){
            mp.put(nums[i], mp.getOrDefault(nums[i], 0)+1);
        }

        PriorityQueue<Pair>pq = new PriorityQueue<>((a,b)->b.val - a.val);
        for(int key : mp.keySet()){
            pq.offer(new Pair(key, mp.get(key)));
        }

        for(int i=0;i<k;i++){
            res[i]=pq.poll().key;
        }
        System.out.println(mp.toString());
        for(int i=0;i<res.length;i++){
            System.out.println(res[i]);
        }
        return res;
    }
    
public int[] productExceptSelf(int[] nums) {

    int n = nums.length;
    int[]res = new int[n];
    int ret = 1;
    res[0]= 1;
    for(int i =0;i<n-1;i++){
        ret +=nums[i];
        res[i+1]= ret;
    }
    ret = 1;
    for(int i = n-1;i>0;i++){
        ret *=nums[i];
        res[i-1]*=ret;
    }

    return res;
   
}   

    public static void main(String[] args) {
        Solution sol = new Solution();
        int []nums = {1,1,1,2,2,3};
        int k = 2;
        sol.topKFrequent(nums, k);
    }
}