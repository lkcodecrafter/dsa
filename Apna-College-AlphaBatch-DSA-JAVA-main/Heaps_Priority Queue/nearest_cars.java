import java.util.*;

public class nearest_cars {

    static class Point implements Comparable<Point>{
        int x,y;
        int distSq;
        int idx;

        public Point(int x, int y, int distSq,int idx){
            this.x = x;
            this.y = y;
            this.distSq = distSq;
            this.idx = idx;
        }

        //we will priotize this queue on the basis of the distSq value
        @Override
        public int compareTo(Point p2){
            return this.distSq - p2.distSq;
        }
    }
    public static void main(String args[]){
        int pts[][] =  {{3,3},
                        {5,-1},
                        {-2,4}};
        int k = 2;

        PriorityQueue<Point> list = new PriorityQueue<>(); // we are making a pq of the Point class

        for(int i =0; i<pts.length; i++){
            int distSq = pts[i][0]*pts[i][0] + pts[i][1]*pts[i][1]; // this is for a^2 + b^2 as the another value in second colum
            // calculating the distance square from the origin
            // distSq = x^2 + y^2
            // value of x is pts[i][0] = 3 and value of y is pts[i][1] = 3 for first point
            // so distSq = 3*3 + 3*3 = 18
            // Value of x is pts[i][0] = 5 and value of y is pts[i][1] = -1 for second point
            // so distSq = 5*5 + -1*-1 = 26
            // // Value of x is pts[i][0] = -2 and value of y is pts[i][1] = 4 for third point
            // so distSq = -2*-2 + 4*4 = 20

            // // we are adding a new Point object to the priority queue
            // pts[i][0] represents the x-coordinate of the point
            // pts[i][1] represents the y-coordinate of the point
            // distSq is the distance squared of the point from the origin (x² + y²)
            // i is the index of the point in the original array, used for identification

            // value of x is pts[i][0] = 3 and value of y is pts[i][1] = 3 for first point
            // distSq = 18 and index i = 0
            // so we are adding Point(3, 3, 18, 0) to the priority queue
            //
            // value of x is pts[i][0] = 5 and value of y is pts[i][1] = -1 for second point
            // distSq = 26 and index i = 1
            // so we are adding Point(5, -1, 26, 1) to the priority queue
            //
            // value of x is pts[i][0] = -2 and value of y is pts[i][1] = 4 for third point
            // distSq = 20 and index i = 2
            // so we are adding Point(-2, 4, 20, 2) to the priority queue

            //list.add(new Point(pts[i][0], pts[i][1], distSq, i));

            list.add(new Point(pts[i][0],pts[i][1], distSq, i)); // we are storing the point x and Y cordinate and also its distance form the origin
        }

        // After adding all points, the priority queue (list) is ordered
// based on distance squared from the origin (smallest first)

// Contents of list (distance-wise):
// Point(3, 3, 18, 0)   -> nearest
// Point(-2, 4, 20, 2)
// Point(5, -1, 26, 1) -> farthest

// When we remove elements from the priority queue:

// First remove():
// returns Point(3, 3, 18, 0)
// printed as: C0

// Second remove():
// returns Point(-2, 4, 20, 2)
// printed as: C2

// Since k = 2, only the first two nearest points are printed


        //printing k numbers of nearest cars
        for(int i =0; i<k; i++){
                // list.remove() removes and returns the point
    // with the smallest distance from the origin
    // because PriorityQueue stores points in sorted order (nearest first)

    // .idx gives the index of that point from the original pts array

    // "C" + idx prints the car number
    // Example:
    // first iteration -> nearest point index = 0 -> prints C0
    // second iteration -> second nearest point index = 2 -> prints C2

            System.out.println("C"+list.remove().idx+" ");
        }
    }
}
