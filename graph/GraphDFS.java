import java.util.ArrayList;
import java.util.List;

class GraphDFS {

    public static void dfs(boolean[] visited, List<List<Integer>> adj, int node) {
        visited[node] = true;
        System.out.print(node + " ");
        for (int i : adj.get(node)) {
            if (!visited[i]) {
                dfs(visited, adj, i);
            }
        }
    }

    public static void main(String[] args) {
        int v = 5;
        List<List<Integer>> adj = new ArrayList<>();
        for (int i = 0; i < v; i++) {
            adj.add(new ArrayList<>());
        }

        // Undirected edges
        adj.get(0).add(1);
        adj.get(1).add(0);
        adj.get(0).add(2);
        adj.get(2).add(0);
        adj.get(1).add(3);
        adj.get(3).add(1);
        adj.get(1).add(4);
        adj.get(4).add(1);

        boolean[] visited = new boolean[v];
        System.out.print("DFS: ");
        dfs(visited, adj, 0);

    }
}