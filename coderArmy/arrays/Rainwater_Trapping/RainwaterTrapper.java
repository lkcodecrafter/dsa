
public class RainwaterTrapper {

    public static int calculateTrappedWater(int[] heightBars) {
        int n = heightBars.length;

        int[] leftMax = new int[n];
        leftMax[0] = heightBars[0];
        for (int i = 1; i < n; i++) {
            leftMax[i] = Math.max(heightBars[i], leftMax[i - 1]);
        }

        int[] rightMax = new int[n];
        rightMax[n - 1] = heightBars[n - 1];
        for (int i = n - 2; i >= 0; i--) {
            rightMax[i] = Math.max(heightBars[i], rightMax[i + 1]);
        }

        int trappedWater = 0;
        for (int i = 0; i < n; i++) {
            int waterLevel = Math.min(leftMax[i], rightMax[i]);
            trappedWater += waterLevel - heightBars[i];
        }

        return trappedWater;
    }

    public static void main(String[] args) {
        int[] bars = {4, 2, 0, 6, 3, 2, 5};
        System.out.println(calculateTrappedWater(bars));
    }
}
