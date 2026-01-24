import java.util.*;

// https://www.youtube.com/watch?v=1ZAotQGnbi4

// Question: Find the Nth Catalan Number
// What are Catalan Numbers?
// The Catalan numbers are a sequence of natural numbers that occur in various counting problems, often involving recursively defined objects.
// They are named after the Belgian mathematician Eugène Charles Catalan (1814–1894).
// Exmaples of problems that can be solved using Catalan numbers include:
// 1. Counting the number of correct ways to match parentheses.
// 2. Counting the number of rooted binary trees with n+1 leaves.
// 3. Counting the number of ways to triangulate a polygon with n+2 sides.
// 4. Counting the number of paths along the edges of a grid that do not cross above the main diagonal.
// 5. Counting the number of non-crossing partitions of a set.
// Catalan Numbers: 1, 1, 2, 5, 14, 42, 132, 429, 1430, ...
// Cn = Σ Ci * Cn-i-1 for i=0 to n-1
// C0 = 1, C1 = 1
// C2 = C0*C1 + C1*C0 = 1*1 + 1*1 = 2
// C3 = C0*C2 + C1*C1 + C2*C0 =
public class Classroom {
  public static int catalanRec(int n) {
    if (n == 0 || n == 1) {
      return 1;
    }

    int ans = 0; //Cn

    for (int i = 0; i <= n-1; i++) {
      ans += catalanRec(i) * catalanRec(n-i-1);
    }

    return ans;
  }

  public static int catalanMem(int n, int dp[]) {
    if (n == 0 || n == 1) {
      return 1;
    }

    if (dp[n] != -1) {
      return dp[n];
    }

    int ans = 0;
    for (int i = 0; i < n; i++) {
      ans += catalanMem(i, dp) * catalanMem(n-i-1, dp);
    }

    return dp[n] = ans;
  }

  //O(n*n)
  public static int catalanTab(int n) {
    int dp[] = new int[n+1];
    dp[0] = 1;
    dp[1] = 1;

    for (int i = 2; i <= n; i++) { //Ci
      for (int j = 0; j < i; j++) {
        dp[i] += dp[j] * dp[i-j-1];
      }
    }

    return dp[n];
  }

  public static void main(String args[]) {
    int n = 4;
    System.out.println(catalanRec(n));

    int dp[] = new int[n+1];
    Arrays.fill(dp, -1);
    System.out.println(catalanMem(4, dp));

    System.out.println(catalanTab(5));
  }
}
