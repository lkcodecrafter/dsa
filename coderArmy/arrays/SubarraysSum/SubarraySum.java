
public class SubarraySum {

    public static void printSubarraysWithSum(int[] arr) {
        int n = arr.length;

        for (int start = 0; start < n; start++) {
            int currentSum = 0;

            for (int end = start; end < n; end++) {
                currentSum += arr[end];

                // Print subarray
                for (int k = start; k <= end; k++) {
                    System.out.print(arr[k] + " ");
                }

                System.out.println("→ Sum: " + currentSum);
            }

            System.out.println(); // blank line between subarrays
        }
    }

    public static void main(String[] args) {
        int[] numbers = {1, 2, 3, 4, 5};
        printSubarraysWithSum(numbers);

        int n = numbers.length;
        System.out.println("Total number of subarrays = " + (n * (n + 1)) / 2);
    }
}
