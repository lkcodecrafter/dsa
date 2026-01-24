import java.util.*;


public class Chocola_Problem {
    
    public static void main(String args[]){
        int n = 4, m = 6; //n,m are rows and coloums cuts
        
        Integer costVer[] = {2,1,3,1,4}; 
        Integer costHori[] = {4,1,2};

        //sorting both array in reverse order
        Arrays.sort(costVer,Collections.reverseOrder());
        Arrays.sort(costHori,Collections.reverseOrder());

        //pointer to track both array
        int h = 0; int v = 0;

        //integer to track the no. of pices
        int hp = 1; int vp = 1;

        int cost = 0;

        while(h < costHori.length && v < costVer.length){

            if(costVer[v] <= costHori[h]){
                cost += (costHori[h]*vp);//cost of that slide * no. of vertical piece
                hp++;//we hava performed a horizontal cut therefore no. of horizontal picies will in increase
                h++;//shifting pointer
            }else{
                cost += (costVer[v]*hp);
                vp++;
                v++;
            }
        }

        //for remaining elements in hori array
        while(h < costHori.length){
            cost += (costHori[h]*vp);
            hp++;
            h++;
        }

        //for remaining element in vertical array
        while( v < costVer.length){
            cost += (costVer[v]*hp);
            vp++;
            v++;
        }


        System.out.println("Min cost of cutting is "+cost);


    }
}


/*

lkcodecrafter: can you help me to understand this code and dry run also.

GitHub Copilot: Certainly! Here’s a clear explanation and a dry run of your code in `Chocola_Problem.java`.

## What does this code do?

This code solves the "Minimum Cost to Cut a Chocolate" problem using a greedy algorithm.  
Given a chocolate bar of size n x m, you are given the costs of making horizontal and vertical cuts. The goal is to cut the chocolate into 1x1 pieces with the minimum total cost.

- `costVer[]`: Cost of making each vertical cut.
- `costHori[]`: Cost of making each horizontal cut.

The cost of each cut is multiplied by the number of pieces it affects (i.e., the number of current segments in the other direction).

## Step-by-step Explanation

1. **Sort the cut costs in descending order**  
   This ensures you always make the most expensive cut first, maximizing its effect (greedy approach).

2. **Initialize pointers and piece counters**  
   - `h` and `v` are pointers for horizontal and vertical cuts.
   - `hp` and `vp` track the current number of horizontal and vertical pieces.

3. **Iterate through both arrays**  
   - At each step, pick the higher cost cut (horizontal or vertical).
   - Update the total cost and increment the corresponding piece counter.

4. **Handle remaining cuts**  
   - If one array is exhausted, process the remaining cuts in the other array.

5. **Print the minimum cost**

---

## Dry Run

Given:
- `costVer = {2,1,3,1,4}` (vertical cuts)
- `costHori = {4,1,2}` (horizontal cuts)

After sorting in descending order:
- `costVer = {4,3,2,1,1}`
- `costHori = {4,2,1}`

Initial values:
- `h = 0`, `v = 0`
- `hp = 1`, `vp = 1`
- `cost = 0`

### Iteration Steps

| Step | costVer[v] | costHori[h] | Action | Cost Added | hp | vp | h | v | Total Cost |
|------|------------|-------------|--------|------------|----|----|---|---|------------|
| 1    | 4          | 4           | Hori   | 4*1 = 4    | 2  | 1  | 1 | 0 | 4          |
| 2    | 4          | 2           | Vert   | 4*2 = 8    | 2  | 2  | 1 | 1 | 12         |
| 3    | 3          | 2           | Vert   | 3*2 = 6    | 2  | 3  | 1 | 2 | 18         |
| 4    | 2          | 2           | Hori   | 2*3 = 6    | 3  | 3  | 2 | 2 | 24         |
| 5    | 2          | 1           | Vert   | 2*3 = 6    | 3  | 4  | 2 | 3 | 30         |
| 6    | 1          | 1           | Hori   | 1*4 = 4    | 4  | 4  | 3 | 3 | 34         |

Now, `h = 3` (end of costHori), but `v = 3` (still 2 elements left in costVer).

Process remaining vertical cuts:
- `cost += 1*4 = 4` (`v=4`, `vp=5`, `cost=38`)
- `cost += 1*4 = 4` (`v=5`, `vp=6`, `cost=42`)

Final output:  
`Min cost of cutting is 42`

---

## Summary

- The code always picks the most expensive cut available.
- Each cut's cost is multiplied by the number of current pieces in the other direction.
- The process continues until all cuts are made.

Let me know if you want a more detailed step-by-step with variable values at each line!


*/