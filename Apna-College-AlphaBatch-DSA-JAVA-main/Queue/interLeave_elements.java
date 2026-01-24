import java.util.*;
public class interLeave_elements {

    public static void inter_leave(Queue<Integer> q)
    {
        //first we will make another queue of first half elements
        Queue <Integer> firstHalf = new LinkedList<>();

        //we will need size for dividing
        int middle = q.size()/2; // do make this variable because if you write directly the value of middle will change in each loop

        for(int i = 0; i<middle; i++){
            firstHalf.add(q.remove());
        }
        System.out.println(firstHalf);
        while(!firstHalf.isEmpty())
        {
            //add the element from first queue
            q.add(firstHalf.remove());
            //move the first element at last of the orignal queue
            q.add(q.remove()); // output: 1 6 2 7 3 8 4 9 5 10  how?
            // 1st iteration: remove 1 from q and add to firstHalf
            // q = 6 7 8 9 10
            // then add 1 to q
            // q = 6 7 8 9 10 1
            // then remove 6 from q and add to last
            // q = 7 8 9 10 1 6
            //2nd iteration: remove 2 from q and add to firstHalf
            // q = 7 8 9 10 1 6
            // then add 2 to q
            // q = 7 8 9 10 1 6 2
            // then remove 7 from q and add to last
            // q = 8 9 10 1 6 2 7
            // and so on...
        }
    }
    public static void main(String args[])
    {
        Queue <Integer> q = new LinkedList<>();

        q.add(1);
        q.add(2);
        q.add(3);
        q.add(4);
        q.add(5);
        q.add(6);
        q.add(7);
        q.add(8);
        q.add(9);
        q.add(10);

        inter_leave(q);

       while(!q.isEmpty()){
        System.out.print(q.remove()+" ");
       }

    }
    
}
