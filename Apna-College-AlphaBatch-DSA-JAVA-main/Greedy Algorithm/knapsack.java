import java.util.*;
public class knapsack {

    public static void main(String args[]){
        int val[] = {60,100,120};
        int weight[] = {10,20,30};
        int W = 50; //bag weight

        //2D array for storing the rate
        double rate[][] = new double[val.length][2];
        
        for(int i=0; i<val.length;i++){
            rate[i][0] = i; //storing index on coloum 1st
            //type casting below is so important or the value can became 0
            rate[i][1] = val[i]/(double)weight[i]; //storing rate on coloum 2nd
            
        }

        //sorting on the basis of coloum 2
        Arrays.sort(rate, Comparator.comparingDouble( o -> o[1]));
         
        int capacity = W;
        int finalVal = 0;

        for(int i = rate.length-1; i>= 0; i--){
            //taking index of first most costly item
            int idx = (int)rate[i][0]; //this will be at zero because we have sorted

            if(capacity >= weight[idx]){ // include all
                finalVal += val[idx];
                capacity -= weight[idx];
            }else{//we will add fraction part

                finalVal += (rate[i][1]*capacity); //here it will add only about that much it can hold remaining capacity
                capacity = 0;
                break;

            }
        }

        System.out.println(finalVal);
    }
    
}


/*

lkcodecrafter: Can you help me to understand this question also dry run the same. also       double rate[][] = new double[val.length][2];

GitHub Copilot: Certainly! Here’s an explanation and a dry run of the code, including the line double rate[][] = new double[val.length][2];.

### What does this code do?
This code solves the Fractional Knapsack problem using a greedy algorithm. Given:
- An array of item values (`val`)
- An array of item weights (`weight`)
- A maximum bag capacity (`W`)

The goal is to maximize the total value in the knapsack, possibly taking fractions of items.

#### Key line explained:
```java
double rate[][] = new double[val.length][2];
```
- This creates a 2D array where each row represents an item.
- `rate[i][0]` stores the index of the item.
- `rate[i][1]` stores the value-to-weight ratio (value per unit weight) for that item.

### Step-by-step Dry Run

#### Input:
- val = {60, 100, 120}
- weight = {10, 20, 30}
- W = 50

#### Step 1: Calculate value-to-weight ratios
For each item:
- Item 0: 60/10 = 6.0
- Item 1: 100/20 = 5.0
- Item 2: 120/30 = 4.0

So, `rate` becomes:
| Index | Ratio |
|-------|-------|
| 0     | 6.0   |
| 1     | 5.0   |
| 2     | 4.0   |

#### Step 2: Sort by ratio (descending)
After sorting (the code sorts ascending, so we process from the end):
| Index | Ratio |
|-------|-------|
| 2     | 4.0   |
| 1     | 5.0   |
| 0     | 6.0   |

But since we process from the end, the order is: 0 (6.0), 1 (5.0), 2 (4.0).

#### Step 3: Fill the knapsack
- Start with capacity = 50, finalVal = 0

1. Take item 0 (weight 10, value 60)
   - capacity = 50 - 10 = 40
   - finalVal = 0 + 60 = 60

2. Take item 1 (weight 20, value 100)
   - capacity = 40 - 20 = 20
   - finalVal = 60 + 100 = 160

3. Take item 2 (weight 30, value 120)
   - Only 20 capacity left, so take 20/30 fraction
   - Add value: 4.0 (ratio) * 20 = 80
   - finalVal = 160 + 80 = 240
   - capacity = 0

#### Step 4: Output
- Prints: 240

### Summary
- The code calculates the best value-to-weight ratio for each item.
- It sorts items by this ratio.
- It fills the knapsack with as much of the highest-ratio items as possible, taking fractions if needed.
- The answer for the given input is 240.

Let me know if you want a more detailed step-by-step table or have any other questions!

*/