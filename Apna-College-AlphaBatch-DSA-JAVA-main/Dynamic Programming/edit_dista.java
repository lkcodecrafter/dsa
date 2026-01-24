// https://www.youtube.com/watch?v=oqfqPEqrKo8
// Edit Distance Problem - Dynamic Programming


public class edit_dista {

    // What is editDistance?
    // Edit distance is the minimum number of operations required to convert one string into another.
    // The operations can be insertion, deletion, or replacement of a character.
    // For example, the edit distance between "kitten" and "sitting" is 3:
    // 1. Replace 'k' with 's' (kitten -> sitten)
    // 2. Replace 'e' with 'i' (sitten -> sittin)
    // 3. Insert 'g' at the end (sittin -> sitting)
    // Hence, the edit distance is 3.

    // Time Complexity: O(n*m)
    // Space Complexity: O(n*m)
    // Can you help to understand the code?
    // Sure! The code implements a dynamic programming approach to calculate the edit distance between two strings.
    // It uses a 2D array `dp` where `dp[i][j]` represents the 
    // edit distance between the first `i` characters of `str1` and the first `j` characters of `str2`.
    // The algorithm initializes the first row and column of the `dp` array to represent the base cases:
    // - If one string is empty, the edit distance is the length of the other string (all insertions or deletions).
    // Then, it iterates through each character of both strings, comparing them:
    // - If the characters are the same, it takes the value from the diagonal cell `dp[i-1][j-1]`.
    // - If the characters are different, it calculates the minimum edit distance considering the three possible operations (insertion, deletion, replacement) and adds one to that minimum.
    // Finally, it returns the value in `dp[n][m]`, which contains the edit distance between the two full strings. 
    // why taken dp[i][j] = dp[i - 1][j - 1]; when characters are same?
    // When the characters are the same, no additional operation is needed to convert one string to the other for that particular character position.
    // Therefore, the edit distance remains the same as it was for the previous characters, which is represented by `dp[i - 1][j - 1]`.
    // This means that the edit distance up to the current characters is equal to the edit distance up to the previous characters, as no new edits are required.

    // why taken dp[][] size as n+1 and m+1?
    // The `dp` array is sized as `(n+1) x (m+1)` to accommodate the base case where one of the strings is empty.
    // The extra row and column (i.e., the 0th row and 0th column) represent the scenario where either `str1` or `str2` has a length of zero.
    // This allows us to easily initialize the edit distances for cases where one string is empty:
    // - `dp[0][j]` represents the edit distance when `str1` is empty, which is simply `j` (all insertions).
    // - `dp[i][0]` represents the edit distance when `str2` is empty, which is `i` (all deletions).
    // By including these base cases in the `dp` array, we can build up the solution for the full strings in a straightforward manner.  

    public static int editDistance(String str1, String str2) {

        int n = str1.length();
        int m = str2.length();
        int dp[][] = new int[n + 1][m + 1];

        // initialize
        for (int i = 0; i < n + 1; i++) {
            for (int j = 0; j < m + 1; j++) {
                if (i == 0) {
                    dp[i][j] = j; // if str1 is empty, we need j operations to convert it to str2 j value here is 0
                }
                if (j == 0) {
                    dp[i][j] = i; // if str2 is empty, we need i operations to convert str1 to empty string i value here is 0
                }
            }
            // final dp[i][j] array will look like this after initialization
            //     ""  e  x  e  c  u  t  i  o  n
            // ""  0  1  2  3  4  5  6  7  8  9
            // i   1  0  0  0  0  0  0  0  0  0
            // n   2  0  0  0  0  0  0  0  0  0
            // t   3  0  0  0  0  0  0  0  0  0
            // e   4  0  0  0  0  0  0  0  0  0
            // n   5  0  0  0  0  0  0  0  0  0
            // t   6  0  0  0  0  0  0  0  0  0
            // i   7  0  0  0  0  0  0  0  0  0  
            // o   8  0  0  0  0  0  0  0  0  0
            // n   9  0  0  0  0  0  0  0  0  0

        }

        // bottom up
        for (int i = 1; i < n + 1; i++) {
            for (int j = 1; j < m + 1; j++) {

                if (str1.charAt(i - 1) == str2.charAt(j - 1)) { // same charecter // i-1 and j-1 value here is 0
                    dp[i][j] = dp[i - 1][j - 1]; // no operation needed bcs characters are same

                } else { // diff
                    int add = dp[i][j - 1] + 1; //add operation // j-1 value here is 0, we are adding character of str2 to str1
                    int del = dp[i - 1][j] + 1; //delete operation // i-1 value here is 0, we are deleting character of str1
                    int rep = dp[i - 1][j - 1] + 1; //replace opetation // i-1 and j-1 value here is 0, we are replacing character of str1 with str2
                    dp[i][j] = Math.min(add, Math.min(del, rep)); // take min of all three operations
                }
            }
        }

        return dp[n][m];
    }

    public static void main(String args[]) {
        String m = "intention";
        String M = "execution"; //ans 5 operation
        
        System.out.println(editDistance(m, M));
    }

}
