# 📈 Best Time to Buy and Sell Stock

## 🧩 Problem Statement

You are given an array `prices[]` where `prices[i]` represents the stock price on the `i`-th day.

- You are allowed to **buy one and sell one share** of the stock.
- You **must buy before you sell**.
- Return the **maximum profit** you can achieve.
- If no profit is possible, return `0`.

---

## ✅ Example

| Input               | Output |
|--------------------|--------|
| [7,1,5,3,6,4]       |   5    |
| [7,6,4,3,1]         |   0    |

---

## 🧠 Approach

1. Set `buyPrice` to a very large value (`∞`).
2. Set `maxProfit = 0`.
3. For each price in the array:
   - If the price is higher than `buyPrice`, calculate `profit = price - buyPrice`.
   - Update `maxProfit = max(maxProfit, profit)`.
   - If the price is lower than `buyPrice`, update `buyPrice`.
4. Return `maxProfit`.

---

🔁 Dry Run on [7,1,5,3,6,4]
Day	Price	buyPrice	Profit	maxProfit
0	7	7	-	0
1	1	1	-	0
2	5	1	4	4
3	3	1	2	4
4	6	1	5	5
5	4	1	3	5

🔚 Final Answer: 5

📌 Notes
Time Complexity: O(n)

Space Complexity: O(1)

Only one transaction allowed (1 buy and 1 sell).


## 💻 Java Code

```java
public class Buying_Stock {

    public static int BuyAndSellStock(int prices[]) {
        int buyPrice = Integer.MAX_VALUE;
        int maxProfit = 0;

        for (int i = 0; i < prices.length; i++) {
            if (buyPrice < prices[i]) {
                int profit = prices[i] - buyPrice;
                maxProfit = Math.max(maxProfit, profit);
            } else {
                buyPrice = prices[i];
            }
        }

        return maxProfit;
    }

    public static void main(String args[]) {
        int prices[] = {7, 1, 5, 3, 6, 4};
        System.out.print(BuyAndSellStock(prices));
    }
}

