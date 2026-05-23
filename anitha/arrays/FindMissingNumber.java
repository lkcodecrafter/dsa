package arrays;

public class FindMissingNumber {

    /*
     * Find missing numbers from an array
     * */
    public static int findMissingNumbers(int[] arr, int count) {

        int i, total;
        total  = (count+1)*(count+2)/2;
        for ( i = 0; i< count; i++) {
            total -= arr[i];
        }
        return total;
    }


public static int findMissingNumber2(int[] arr, int n) {
    int total = 0;

    // Step 1: Sum numbers from 1 to n
    for (int i = 1; i <= n; i++) {
        total += i;
    }

    // Step 2: Subtract array elements
    for (int i = 0; i < arr.length; i++) {
        total -= arr[i];
    }

    return total;
}

    public static void main(String[] args) {
        int[] arr = {1, 2, 4,6, 3, 7, 8};
		// [1,3,4] =8
		//6-1 =2
		//2 - 3 = -1 
		//-1 - 4 =  
        System.out.println(findMissingNumbers(arr, arr.length));
    }
}
