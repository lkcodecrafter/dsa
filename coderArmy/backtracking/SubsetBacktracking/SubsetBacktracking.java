
import java.util.*;

public class SubsetBacktracking {

    public static void generateSubsets(int index, List<Integer> current, int[] nums) {
        // Print current subset
        System.out.println(current);

        for (int i = index; i < nums.length; i++) {
            current.add(nums[i]);                     // Choose
            generateSubsets(i + 1, current, nums);    // Explore
            current.remove(current.size() - 1);       // Un-choose (backtrack)
        }
    }

    public static void main(String[] args) {
        int[] nums = {1, 2, 3};
        generateSubsets(0, new ArrayList<>(), nums);
    }
}
