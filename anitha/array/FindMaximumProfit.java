
public class FindMaximumProfit {

public static int findMaximumProfit(int[] stockPrices)
{
    int maxProfit = 0;
    int minPrice = Integer.MAX_VALUE;

    for (int i = 0; i < stockPrices.length; i++) {
        if (stockPrices[i] < minPrice)
        {
            minPrice = stockPrices[i];
        }
        else
        {
            int profit = stockPrices[i] - minPrice;
            if (profit > maxProfit) 
            {
                maxProfit = profit;
            }
        }
    }

    return maxProfit;
}

public static void main(String[] args) {
    int[] stockPrices = {100, 180, 260, 310, 40, 535, 695};
    int maxProfit = findMaximumProfit(stockPrices);
    System.out.println("Maximum Profit: " + maxProfit);
}
}