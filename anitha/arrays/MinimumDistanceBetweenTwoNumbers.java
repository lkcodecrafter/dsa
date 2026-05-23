package arrays;



public class MinimumDistanceBetweenTwoNumbers {


public static int findMinimumDistance(int[] arr, int n, int x, int y) {
    int minDist = Integer.MAX_VALUE;

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (((arr[i] == x && arr[j] == y) ||
                 (arr[i] == y && arr[j] == x)) &&
                 Math.abs(i - j) < minDist) {

                minDist = Math.abs(i - j);
            }
        }
    }
    return minDist;
}

/*

🔍 Dry Run (simple example)
Input
arr = [3, 5, 4, 2, 6, 5, 6]
x = 5, y = 6
Step-by-step

We check all pairs:

i=1 (5), j=4 (6) → distance = 3 → minDist = 3
i=1 (5), j=6 (6) → distance = 5 → ignore (larger)
i=5 (5), j=6 (6) → distance = 1 → minDist = 1 ✅
Final Answer
1

*/


// O(n)
public static int findMinimumDistance(int[] arr, int n, int x, int y) {
    int minDist = Integer.MAX_VALUE;
    int prevIndex = -1;

    for (int i = 0; i < n; i++) {
        if (arr[i] == x || arr[i] == y) {

            if (prevIndex != -1 && arr[i] != arr[prevIndex]) {
                minDist = Math.min(minDist, i - prevIndex);
            }

            prevIndex = i;
        }
    }

    return minDist;
}

/*

🔍 Dry Run of Optimized Version
Input
[3, 5, 4, 2, 6, 5, 6]
x = 5, y = 6
Walkthrough
i=1 → 5 → prevIndex = 1
i=4 → 6 → diff = 4-1 = 3 → minDist = 3
i=5 → 5 → diff = 5-4 = 1 → minDist = 1
i=6 → 6 → diff = 6-5 = 1 → still 1


*/

    public static void main(String[] args) {
        int[] arr = {3, 5, 4, 2, 6, 5, 6, 6, 5, 4, 8, 3};
        int n = arr.length;
        int x = 3;
        int y = 6;
        System.out.println(findMinimumDistance(arr, n, x, y));
    }
}
