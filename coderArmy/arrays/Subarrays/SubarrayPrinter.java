
import java.util.*;

public class SubarrayPrinter {

    public static void printAllSubarrays(int[] arr) {
        for (int i = 0; i < arr.length; i++) {
            int start = i;
            for (int j = i; j < arr.length; j++) {
                int end = j;
                for (int k = start; k <= end; k++) {
                    System.out.print(arr[k] + " ");
                }
                System.out.println();
            }
            System.out.println();
        }
    }

    public static void main(String args[]) {
        int[] numbers = {2, 4, 6, 8, 10};
        printAllSubarrays(numbers);

        int n = numbers.length;
        int totalSubarrays = (n * (n + 1)) / 2;
        System.out.println("Total subarrays = " + totalSubarrays);
    }
}
