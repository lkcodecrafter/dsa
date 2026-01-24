
import java.util.PriorityQueue;


class Practice{

    static class Pair implements Comparable<Pair>{

        int val;
        int ind;

        public Pair(int val, int inx){
            this.val = val;
            this.ind     = inx;
        }


        @Override
        public int compareTo(Pair o) {
           return o.val - this.val;
        }
        
    }

public static void main(String[] arg){
 int arr[] = {1,3,-1,-3,5,3,6,7};
 int k =3;
 int res[] = new int[arr.length - k +1];

    PriorityQueue<Pair>pg = new PriorityQueue<>();
    
    for(int i =0;i<k;i++){
        pg.add(new Pair(arr[i], i));
    }

    res[0] = pg.peek().val;

    for(int i=k;i<arr.length;i++){
        while(pg.size() > 0 && pg.peek().val <= (i-k)){
            pg.remove();
        }
        pg.add(new Pair(arr[i], i));
        res[i-k+1]= pg.peek().val;

    }


    for(int i=0;i<res.length;i++){
        System.out.println("max " + res[i] + " ");
    }
}

}