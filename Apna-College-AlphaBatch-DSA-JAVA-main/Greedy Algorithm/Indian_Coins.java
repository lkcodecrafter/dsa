import java.util.*;

public class Indian_Coins {
    public static void main(String args[]){
        Integer coins[]= {1,2,5,10,20,50,100,500,2000};

        //sort the array in decending order
        Arrays.sort(coins,Comparator.reverseOrder());

        //to save which note is used
        ArrayList <Integer> ans = new ArrayList<>();

        int coinsCount = 0;
        int amount = 590;

        for(int i = 0; i<coins.length;i++){
            if(coins[i]<=amount){
                while(coins[i]<=amount){
                    coinsCount++;
                    ans.add(coins[i]);
                    amount-= coins[i];

                }
            }
        }

        System.out.println("no. of coins = "+coinsCount);
        for(int i = 0; i<ans.size(); i++){
            System.out.print(ans.get(i)+" ");
        }
    }
}


/*


lkcodecrafter: Can you help me to understand this question also dry run the same.

GitHub Copilot: Certainly! Here’s an explanation and a dry run of your code in `Indian_Coins.java`:

## Problem Explanation

The code solves the "Minimum Coins for Change" problem using a greedy algorithm.  
Given an amount (here, 590), and a set of Indian coin/note denominations, the goal is to find the minimum number of coins/notes needed to make up that amount.

### Steps:
1. Sort the denominations in descending order.
2. For each denomination, use as many as possible until the remaining amount is less than that denomination.
3. Move to the next smaller denomination and repeat.
4. Track the coins/notes used and their count.

---

## Dry Run (amount = 590)

### Denominations (after sorting):
2000, 500, 100, 50, 20, 10, 5, 2, 1

### Steps:
- Start with amount = 590, coinsCount = 0, ans = []

1. 2000: 2000 > 590 → skip
2. 500: 500 ≤ 590  
   - Use 500: amount = 590 - 500 = 90, coinsCount = 1, ans = [500]
3. 100: 100 > 90 → skip
4. 50: 50 ≤ 90  
   - Use 50: amount = 90 - 50 = 40, coinsCount = 2, ans = [500, 50]
5. 20: 20 ≤ 40  
   - Use 20: amount = 40 - 20 = 20, coinsCount = 3, ans = [500, 50, 20]  
   - Use 20: amount = 20 - 20 = 0, coinsCount = 4, ans = [500, 50, 20, 20]

Now, amount = 0, so the loop ends.

### Output:
- no. of coins = 4
- Coins used: 500 50 20 20

---

## Summary

- The code finds the minimum number of coins/notes needed for a given amount using a greedy approach.
- For amount 590, the answer is 4 coins/notes: 500, 50, 20, 20.

Let me know if you want a step-by-step trace for a different amount or further explanation!

*/