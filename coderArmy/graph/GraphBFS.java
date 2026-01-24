import java.util.ArrayDeque;
import java.util.ArrayList;
import java.util.LinkedList;
import java.util.List;
import java.util.Queue;

public class GraphBFS {

    public static void bfs(boolean[]visited, List<List<Integer>>adj, int start){
        Queue<Integer>queue= new LinkedList<>();
        queue.offer(start);
        visited[start]=true;
        while (!queue.isEmpty()) {
            int data = queue.poll();
            System.out.println("node "+ data);
            for(int neighbor : adj.get(data)){
                if (!visited[neighbor]) {
                    visited[neighbor]=true;
                    queue.offer(neighbor);
                }
            }
        }

    }

    public static void main(String[] args) {
        int V = 5;
        List<List<Integer>>adj=new ArrayList<>();
        for(int i=0;i<V;i++){
            adj.add(new ArrayList<>());
        }

/*
0 → 1, 2  
1 → 0, 3, 4  
2 → 0  
3 → 1  
4 → 1
*/

        adj.get(0).add(1);
        adj.get(1).add(0);
        adj.get(0).add(2);
        adj.get(2).add(0);
        adj.get(1).add(3);
        adj.get(3).add(1);
        adj.get(1).add(4);
        adj.get(4).add(1);

           boolean[] visited = new boolean[V];
        System.out.print("BFS: ");
        bfs(visited,adj,0);

    }
}
