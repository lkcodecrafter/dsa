public class BubbleSort {
    public static void bubbleSort(int[] arr) {
        int n = arr.length;

        for (int i = 0; i < n - 1; i++) { // n-1 passes
            for (int j = 0; j < n - i - 1; j++) { // each pass up to unsorted part
                if (arr[j] > arr[j + 1]) {
                    // swap arr[j] and arr[j+1]
                    int temp = arr[j];
                    arr[j] = arr[j + 1];
                    arr[j + 1] = temp;
                }
            }
        }
    }

    public static void main(String[] args) {
        int[] arr = {5, 2, 4, 1};
        bubbleSort(arr);

        for (int num : arr) {
            System.out.print(num + " ");
        }
    }
}

/*
 * 🫧 Bubble Sort – Simple Explanation
Idea:
In Bubble Sort, we repeatedly compare two adjacent elements and swap them if they are in the wrong order.
After every full pass, the largest element "bubbles up" to the end.

🔁 Step-by-Step Process
Given: arr = [5, 2, 4, 1]

We do multiple passes:

Compare pairs: If arr[i] > arr[i+1], swap them

After 1st pass, largest number will be at the end

Repeat for n-1 passes (n = size of array)

📊 Dry Run
plaintext
Copy
Edit
arr = [5, 2, 4, 1]

Pass 1:
[5, 2, 4, 1] → 5 > 2 → swap → [2, 5, 4, 1]
[2, 5, 4, 1] → 5 > 4 → swap → [2, 4, 5, 1]
[2, 4, 5, 1] → 5 > 1 → swap → [2, 4, 1, 5]

Pass 2:
[2, 4, 1, 5] → 2 < 4 → no swap
[2, 4, 1, 5] → 4 > 1 → swap → [2, 1, 4, 5]
[2, 1, 4, 5] → 4 < 5 → no swap

Pass 3:
[2, 1, 4, 5] → 2 > 1 → swap → [1, 2, 4, 5]
[1, 2, 4, 5] → sorted ✅
 */