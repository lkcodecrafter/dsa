import java.util.PriorityQueue;

// https://leetcode.com/problems/k-closest-points-to-origin/description/

public class PriorityQueues {

    public static void main(String args[]){

        PriorityQueue <Integer> pq = new PriorityQueue<>();

        pq.add(3);
        pq.add(7);
        pq.add(4);
        pq.add(1);

        /*when the PriorityQueue is of integers the first priority is give to 
         smallest number as the accending order so when we remove the element
         they come in accending order */

         while(!pq.isEmpty()){
            System.out.print(pq.peek()+" "); // output 1 3 4 7
            pq.remove();
         }

    }
    
}
