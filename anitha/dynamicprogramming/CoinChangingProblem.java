package dynamicprogramming;

public class CoinChangingProblem {

    /*
     * Given coin denominations and the total amount, find out the number​ of ways
     * to make the change.
     * Denominations: 1, 2, 5
     * Amount: 7
     * Total Methods: 6
     *
     * Runtime Complexity:
     * O(m n) where m is number of denominations and n is amount.
     *
     * Memory Complexity:
     * Linear, O(n) where n is the amount.
     *
     * Dynamic programming is a problem solving approach which is used when naive
     * approach results in
     * exponential time complexity. To apply dynamic programming approach, the
     * problem to be solved must
     * have optimal substructure i.e. optimal solution of the problem at hand could
     * be achieved by
     * leveraging the optimal solutions of its subproblems and overlapping
     * sub-problems i.e. using
     * pre-computed values for solved sub-problems so that we don't have to solve
     * them again.
     * The coin changing problem has both optimal substructure i.e it can be easily
     * divided to simpler
     * problems and they can be solved to find final solution and it also satisfies
     * the property of
     * overlapping sub problems i.e. previously solved sub problem results can be
     * used multiple times.
     *
     *
     */
    protected static int solveCoinChangeDp(int[] denominations,
            int amount) {

        int[] solution = new int[amount + 1];
        solution[0] = 1;

        for (int den : denominations) {
            for (int i = den; i < (amount + 1); ++i) {
                solution[i] += solution[i - den]; // means of solution[i]+ solution[i - den]
                // dry run for [1,2,3], amount = 4
                // i=1, den = 1
                // solution[1] = solution[1]+solution[0] = 0+1 = 1

                // i=2, den = 1
                // solution[2] = solution[2]+solution[1] = 0+1 = 1

                // i=3, den = 1
                // solution[3] = solution[3]+solution[2] = 0+1 = 1

                // i=4, den = 1
                // solution[4] = solution[4]+solution[3] = 0+1 = 1

                // i=1, den = 2
                // solution[1] = solution[1]+solution[0] = 1+1 = 2

                // i=2, den = 2
                // solution[2] = solution[2]+solution[1] = 1+2 = 3

                // i=3, den = 2
                // solution[3] = solution[3]+solution[2] = 1+3 = 4

                // i=4, den = 2
                // solution[4] = solution[4]+solution[3] = 1+4 = 5

                // i=1, den = 3
                // solution[1] = solution[1]+solution[0] = 2+1 = 3

                // i=2, den = 3
                // solution[2] = solution[2]+solution[1] = 3+3 = 6

                // i=3, den = 3
                // solution[3] = solution[3]+solution[2] = 4+6 = 10

                // i=4, den = 3
                // solution[4] = solution[4]+solution[3] = 5+10 = 15

                // final solution[4] = 15

                // One more dry run with [1,2,5], amount = 7
                // i=1, den=1, sol[1] = sol[1]+sol[0] = 0+1 = 1
                // i=2, den=1, sol[2] = sol[2]+sol[1] = 0+1 = 1
                // i=3, den=1, sol[3] = sol[3]+sol[2] = 0+1 = 1
                // i=4, den=1, sol[4] = sol[4]+sol[3] = 0+1 = 1
                // i=5, den=1, sol[5] = sol[5]+sol[4] = 0+1 = 1
                // i=6, den=1, sol[6] = sol[6]+sol[5] = 0+1 = 1
                // i=7, den=1, sol[7] = sol[7]+sol[6] = 0+1 = 1

                // i=1, den=2, sol[1] = sol[1]+sol[0] = 1+1 = 2
                // i=2, den=2, sol[2] = sol[2]+sol[1] = 1+2 = 3
                // i=3, den=2, sol[3] = sol[3]+sol[2] = 1+3 = 4
                // i=4, den=2, sol[4] = sol[4]+sol[3] = 1+4 = 5
                // i=5, den=2, sol[5] = sol[5]+sol[4] = 1+5 = 6
                // i=6, den=2, sol[6] = sol[6]+sol[5] = 1+6 = 7
                // i=7, den=2, sol[7] = sol[7]+sol[5] = 1+7 = 8

                // i=1, den=5, sol[1] = sol[1]+sol[0] = 2+1 = 3
                // i=2, den=5, sol[2] = sol[2]+sol[1] = 3+3 = 6
                // i=3, den=5, sol[3] = sol[3]+sol[2] = 4+6 = 10
                // i=4, den=5, sol[4] = sol[4]+sol[3] = 5+10 = 15
                // i=5, den=5, sol[5] = sol[5]+sol[4] = 6+15 = 21
                // i=6, den=5, sol[6] = sol[6]+sol[5] = 7+21 = 28
                // i=7, den=5, sol[7] = sol[7]+sol[5] = 8+21 = 29

                // final sol[7] = 29

            }
            // Currently my dry run is den = 2 and i = 2. What will be the next value of i
            // i++ => 3
            // den is 2 and i is 3 so it will execute the inner loop
            // sol[3] = sol[3]+sol[1] => 4+2 = 6

            // solu[3] how is it 4? -
        }
        return solution[solution.length - 1];
    }

    // T.C => O(amount) means amount+1 number of times
    // S.C => O(amount) means amount+1 size of array

    public static void main(String[] args) {
        int[] denominations = new int[] { 1, 5, 10 };
        System.out.println("Combinations (DP): " + solveCoinChangeDp(denominations, 356));
    }
}
