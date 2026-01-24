import java.util.ArrayList;
import java.util.List;
import java.util.*;

public class CycleUndirectedDFS {
    public static boolean hasCycle(int node, int parent, boolean[] visited, List<List<Integer>> adj) {
        visited[node] = true;

        for (int neighbor : adj.get(node)) {
            if (!visited[neighbor]) {
                if (hasCycle(neighbor, node, visited, adj)) return true;
            } else if (neighbor != parent) {
                return true; // cycle found
            }
        }
        return false;
    }

    public static boolean isCyclic(int V, List<List<Integer>> adj) {
        boolean[] visited = new boolean[V];

        for (int i = 0; i < V; i++) {
            if (!visited[i]) {
                if (hasCycle(i, -1, visited, adj)) return true;
            }
        }
        return false;
    }

    public static void main(String[] args) {
        int V = 4;
        List<List<Integer>> adj = new ArrayList<>();
        for (int i = 0; i < V; i++) adj.add(new ArrayList<>());

        // undirected edges
        adj.get(0).add(1); adj.get(1).add(0);
        adj.get(1).add(2); adj.get(2).add(1);
        adj.get(2).add(0); adj.get(0).add(2); // cycle here
        adj.get(1).add(3); adj.get(3).add(1);

        if (isCyclic(V, adj)) {
            System.out.println("Cycle Detected ✅");
        } else {
            System.out.println("No Cycle ❌");
        }
    }
}
