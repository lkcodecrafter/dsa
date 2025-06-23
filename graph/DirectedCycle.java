import java.util.*;

public class DirectedCycle {
    public static boolean hasCycle(int node, boolean[] visited, boolean[] recStack, List<List<Integer>> adj) {
        visited[node] = true;
        recStack[node] = true;

        for (int neighbor : adj.get(node)) {
            if (!visited[neighbor]) {
                if (hasCycle(neighbor, visited, recStack, adj)) return true;
            } else if (recStack[neighbor]) {
                return true; // back edge → cycle
            }
        }

        recStack[node] = false; // done exploring this path
        return false;
    }

    public static boolean isCyclic(int V, List<List<Integer>> adj) {
        boolean[] visited = new boolean[V];
        boolean[] recStack = new boolean[V];

        for (int i = 0; i < V; i++) {
            if (!visited[i]) {
                if (hasCycle(i, visited, recStack, adj)) return true;
            }
        }
        return false;
    }

    public static void main(String[] args) {
        int V = 4;
        List<List<Integer>> adj = new ArrayList<>();
        for (int i = 0; i < V; i++) adj.add(new ArrayList<>());

        adj.get(0).add(1);
        adj.get(1).add(2);
        adj.get(2).add(0); // cycle here
        adj.get(1).add(3);

        if (isCyclic(V, adj)) {
            System.out.println("Cycle Detected ✅");
        } else {
            System.out.println("No Cycle ❌");
        }
    }
}
