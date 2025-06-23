import java.util.ArrayList;
import java.util.List;

class GraphList {

//For a graph with 5 nodes and edges:
//(0 -> 1), (0 -> 4), (1 -> 2), (1 -> 3), (1 -> 4), (2 -> 3), (3 -> 4)
 
    public static void main(String[] args) {
        int V = 5; // number of vertices
        List<List<Integer>> adj = new ArrayList<>();

        for (int i = 0; i < V; i++) {
            adj.add(new ArrayList<>());
        }

        // add edges
        adj.get(0).add(1);
        adj.get(0).add(4);
        adj.get(1).add(2);
        adj.get(1).add(3);
        adj.get(1).add(4);
        adj.get(2).add(3);
        adj.get(3).add(4);

        // print
        for (int i = 0; i < V; i++) {
            System.out.print("Node " + i + ": ");
            for (int neighbor : adj.get(i)) {
                System.out.print(neighbor + " ");
            }
            System.out.println();
        }
    }
}
