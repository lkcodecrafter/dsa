import java.util.*;

// Leetcode Q1167
// What we have to do is to connect the ropes with minimum cost
// we will use min-heap to always connect the smallest two ropes first
// then add the new rope back to the heap and repeat the process until one rope is left
// The cost of connecting two ropes is equal to the sum of their lengths
// By default, Java's PriorityQueue implements a min-heap
// like min priority queue will be as follows
// 2,3,3,4,6
// first we will connect 2 and 3 -> cost = 5
// new ropes -> 3,4,5,6
// then we will connect 3 and 4 -> cost = 7
// new ropes -> 5,6,7
// then we will connect 5 and 6 -> cost = 11
// new ropes -> 7,11
// finally we will connect 7 and 11 -> cost = 18
// total cost = 5 + 7 + 11 + 18 = 41
public class Connect_N_Ropes {
    public static void main(String args[]){
        int ropes[] = {2,3,3,4,6};

        PriorityQueue<Integer> pq = new PriorityQueue<>();
        //adding all elements in PQ
        for(int i =0; i<ropes.length; i++){
            pq.add(ropes[i]);
        }

        System.out.println(pq.toString());
        System.out.println("Connecting ropes....");
        System.out.println("---------------------");
        int cost = 0;

        while(pq.size()>1){
            int min = pq.remove();
            int min2 = pq.remove();

            cost += min+min2;
            pq.add(min+min2);

            System.out.println(pq.toString());
        }

        System.out.println("Cost of cutting rope is : " +cost);
    }
}
