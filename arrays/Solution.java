class Solution {

    //Q1. Move all zeroes to the end of the array
    public void moveZeroes(int[] n ums)  {
        int i  = 0;   
        for (int j = 0; j < nums.length; j++) {
            if (nums[j]   != 0) {
                int tem p  = nums[j];
                nums[j] = nums[i];
                nums[i] = temp;
            }
        }
    }

    //Q2. 88. Merge Sorted Array
    public void merge(int[] nums1, int m, int[] nums2, int n) {
        int i = 0, j = 0, k = 0;
        int[] res = new int[m + n];
        while (i < m && j < n) {
            if (nums1[i] < nums2[j]) {
                res[k++] = nums1[i++];
            } else {
                res[k++] = nums2[j++];
            }
        }
        while (i < m) {
            res[k++] = nums1[i++];
        }
        while (j < n) {
            res[k++] = nums2[j++];
        }

        // Copy merged result back to nums1
        for (int l = 0; l < m + n; l++) {
            nums1[l] = res[l];
        }
    }

    //Q3. 169. Majority Element
    public int majorityElement(int[] nums) {
        HashMap<Integer, Integer> map = new HashMap<>();
        int n = nums.length;
        for (int num : nums) {
            map.put(num, map.getOrDefault(num, 0) + 1);
            if (map.get(num) > n / 2) {
                return num;
            }
        }
        return -1;
    }

    //Function to reverse array 
    static void reverseArray(int arr[], int n) {
        int p1 = 0, p2 = n - 1;
        while (p1 < p2) {
            int tmp = arr[p1];
            arr[p1] = arr[p2];
            arr[p2] = tmp;
            p1++;
            p2--;
        }
        printArray(arr, n);
    }

    static int findLargestElement(int arr[]) {
        int max = arr[0];
        for (int i = 0; i < arr.length; i++) {
            if (arr[i] > max) {
                max = arr[i];
            }
        }
        return max;
    }

    static int SmallestElement(int arr[]) {
        int min = arr[0];
        for (int i = 0; i < arr.length; i++) {
            if (arr[i] < min) {
                min = arr[i];
            }
        }
        return min;
    }

    public int[] twoSum(int[] nums, int target) {
        HashMap<Integer, Integer> map = new HashMap<>();
        for (int i = 0; i < nums.length; i++) {
            int need = target - nums[i];
            if (map.containsKey(need)) {
                return new int[] { i, map.get(need) };
            }
            map.put(nums[i], i);
        }
        return new int[] { -1, -1 };
    }

    public static void rotate(int[] nums, int k) {
        int n = nums.length;
        k = k % n; // handle if k > n

        // Reverse the whole array
        reverse(nums, 0, n - 1);

        // Reverse first k elements
        reverse(nums, 0, k - 1);

        // Reverse the rest
        reverse(nums, k, n - 1);
    }
    
    public int findKthLargest(int[] nums, int k) {
         PriorityQueue<Integer> pg = new PriorityQueue();
        for (int num : nums) {
            pg.add(num);
            if (pg.size() > k) {
                pg.remove();
            }
        }
        return pg.peek();
    }

    public int maxSubArray(int[] nums) {
        int sum = 0;
        int max_sum = nums[0];
        for (int i = 0; i < nums.length; i++) {
            sum += nums[i];
            if (sum > max_sum) {
                max_sum = sum;
            }
            if (sum < 0) {
                sum = 0;
            }
        }
        return max_sum;
    }    
}