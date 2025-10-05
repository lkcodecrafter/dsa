import java.util.*;

class TopKElements {

    public int[] topKFrequent(int[] nums, int k) {
        int[] res = new int[k];
        HashMap<Integer,Integer>map = new HashMap<>();
        for(int num : nums){
            map.put(num, map.getOrDefault(num, 0)+1);
        }
        PriorityQueue<Pair>pq = new PriorityQueue<>((a, b)-> b.val - a.val);
        for(int key : map.keySet()){
            pq.offer(new Pair(key, map.get(key)));
        }
        for(int i = 0 ;i<k;i++){
            res[i]=pq.poll().key;
        }
        return res;
    }

    class Pair{
        int key, val;
        Pair(int k, int v){
            this.key=k;
            this.val= v;
        }
    }

    public static void main(String[] args) {

    }
}