public class MergeSort {

    public static void mergeSort(int[] arr, int left, int right) {
        if (left >= right) {
            return;
        }
        int mid = (left + right) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right); // Merge both halves
    }

    public static void merge(int[] arr, int left, int mid, int right){
        int[]result = new int[right-left+1];
        int i = left;
        int j = mid+1;
        int k=0;
         
        while (i<=mid && j<=right) {
            if(arr[i]<=arr[j]){
                result[k++]=arr[i++];
            }else{
                result[k++]=arr[j++];
            }
        }
        while(i<=mid) {
            result[k++]=arr[i++];
        }
        while (j<=right) {
            result[i++]=arr[j++];
        }
        for(int x=0;x<result.length;x++){
            arr[left+x]=result[x];
        }
        
    }

    public static void main(String[] args) {
        int[] arr = { 5, 2, 4, 1 };
        mergeSort(arr, 0, arr.length - 1);

        for (int num : arr) {
            System.out.print(num + " ");
        }
        
    }
}