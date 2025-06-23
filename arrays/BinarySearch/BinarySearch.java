
import java.util.*;

public class BinarySearch {

    public static int performBinarySearch(int[] numbers, int key) {
        int start = 0;
        int end = numbers.length - 1;

        while (start <= end) {
            int mid = (start + end) / 2;

            if (numbers[mid] == key) {
                return mid;
            }

            if (numbers[mid] < key) {
                start = mid + 1;
            } else {
                end = mid - 1;
            }
        }

        return -1; // key not found
    }

    public static void main(String[] args) {
        int[] numbers = {2, 4, 6, 8, 10, 12, 14, 16};
        int key = 4;
        int resultIndex = performBinarySearch(numbers, key);

        if (resultIndex != -1) {
            System.out.println("Your key is at index: " + resultIndex);
        } else {
            System.out.println("Key not found.");
        }
    }
}
