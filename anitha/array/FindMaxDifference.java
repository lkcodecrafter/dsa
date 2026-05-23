
/*
     * Find the maximum difference between the values in an array such that the largest values always comes after the
     * smallest value
     * Input: {2, 3, 10, 6, 4, 8, 1}
     * Output: 8
     *  Step 1) Set min value as arr[0] -> a
     *  Step 2) set max difference as arr[1] - arr[0]; -> b
     *  Step 3) Iterate and check if the value is > minValue.
     *  Step 4) If it is greater, then get the difference between the two values & check if the difference > max difference (b). If the difference is > set this diff as max difference
     *  Step 5) If it is less than minValue, set this value as minValue
     * */

public class FindMaxDifference {

    // Time Complexity : O(n)
    // Space Complexity : O(1)
    // Q1. Find the maximum difference between the values in an array such that the largest values always comes after the
    // smallest value
    public int findMaxDistance(int[] nums) {
        int maxDiff = nums[1] - nums[0];
        int minValue = nums[0];
        for (int value : nums) {
            if (minValue > value) {
                minValue = value;
            } else {
                maxDiff = Math.max(maxDiff, value - minValue);

            }
        }
        return maxDiff;
    }

    // Q2. Find the maximum product between the values in an array such that the largest values always comes after the
    // smallest value
    public static int findMaxProduct(int arr[], int n) {
        int maxProd = arr[1] * arr[0];
        int minValue = arr[0];
        for(int value : arr){
            if(minValue > value){
                minValue = value;
            }else{
                maxProd = Math.max(maxProd, value * minValue);
            }
        }
        return maxProd;
    }
    public static void main(String[] args) {
        int[] nums = {2, 3, 10, 6, 4, 8, 1};
        FindMaxDifference fmd = new FindMaxDifference();
        System.out.println(fmd.findMaxDistance(nums));
    }
}


// Dry Run simple : 
// maxDiff = 1, minValue = 2
// value = 2, minValue = 2, maxDiff = 1
// value = 3, minValue = 2, maxDiff = 1
// value = 10, minValue = 2, maxDiff = 8
// value = 6, minValue = 2, maxDiff = 8
// value = 4, minValue = 2, maxDiff = 8
// value = 8, minValue = 2, maxDiff = 8
// value = 1, minValue = 1, maxDiff = 8
