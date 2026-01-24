import java.util.*;

public class Weakest_Soldier  {

    static class Row implements Comparable<Row>{
        int soldiers;
        int idx;

        public Row(int soldiers,int idx){
            this.soldiers = soldiers;
            this.idx = idx;
        }

        @Override
        public int compareTo(Row r2){
            if(this.soldiers == r2.soldiers){
                return this.idx - r2.idx;
            }else{
                return this.soldiers - r2.soldiers;
            }
        }
    }
    public static void main(String args[]) {
        int army[][] = { { 1, 0, 0, 0 },
                { 1, 1, 1, 1 },
                { 1, 0, 0, 0 },
                { 1, 0, 0, 0 } };
        int key = 2;

        PriorityQueue<Row> pq = new PriorityQueue<>();
        
        //taking the values of each row specificaly

        for(int i =0; i<army.length; i++){
            int count = 0;
            for(int j = 0; j<army[0].length; j++){
                count+= army[i][j] == 1 ? 1 : 0;
            }

            pq.add(new Row(count,i));
        }

        for(int i =0; i<2; i++){
            System.out.print("R"+pq.remove().idx+" ");
        }
    }
}

/*
User: Can you help me to understand this problem and dry run also.

GitHub Copilot: I'll read the file to understand the problem. 

Read [](file:///c%3A/Users/lalit.k/lalit/d/dsa/Apna-College-AlphaBatch-DSA-JAVA-main/Heaps_Priority%20Queue/Weakest_Soldier.java)

Perfect! Let me explain this problem and do a dry run for you.

## Problem Understanding

**The Weakest Soldiers Problem:**
You have a 2D matrix representing an army where:
- `1` represents a soldier present
- `0` represents no soldier
- Each row represents soldiers in a particular column
- Task: Find the `k` weakest rows (rows with fewest soldiers)

**Key Points:**
1. Count the number of soldiers (1s) in each row
2. If two rows have the same number of soldiers, the one with a smaller index (row number) is weaker
3. Return the indices of the `k` weakest rows

## How the Solution Works

The code uses a **min-heap (Priority Queue)** with a custom comparator:
- Stores each row's soldier count and row index as a `Row` object
- Compares rows: First by soldier count (ascending), then by index (ascending)
- Removes the top `k` elements (weakest rows)

## Dry Run

**Input:**
```
army = [[1,0,0,0],
        [1,1,1,1],
        [1,0,0,0],
        [1,0,0,0]]
key = 2
```

**Step-by-step execution:**

| Row | Index | Soldier Count |
|-----|-------|----------------|
| 0   | 0     | 1              |
| 1   | 1     | 4              |
| 2   | 2     | 1              |
| 3   | 3     | 1              |

**Building Priority Queue:**
- Row(1, 0) added
- Row(4, 1) added
- Row(1, 2) added
- Row(1, 3) added

**Priority Queue (Min-heap order):**
```
        Row(1,0)
       /        \
    Row(1,2)   Row(1,3)
    /
Row(4,1)
```

(Rows with 1 soldier sorted by index: 0, 2, 3; then row with 4 soldiers)

**Remove 2 weakest (key = 2):**
1. First removal: `Row(1, 0)` → Output: **R0**
2. Second removal: `Row(1, 2)` → Output: **R2**

**Output:** `R0 R2`

These are the weakest soldiers because rows 0, 2, and 3 have the fewest soldiers (1 each), and we pick the first 2 by index order.

*/