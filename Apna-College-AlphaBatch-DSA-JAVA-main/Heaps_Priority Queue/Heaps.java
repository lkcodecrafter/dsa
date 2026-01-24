import java.util.*;

// What is a heap?
// A heap is a special tree-based data structure that satisfies the heap property.
// In a max heap, for any given node, the value of the node is greater than
// or equal to the values of its children. In a min heap, the value of the
// node is less than or equal to the values of its children.
// Heaps are commonly used to implement priority queues, where the highest
// (or lowest) priority element is always at the root of the heap.
// Heaps are also used in algorithms like heapsort and for efficiently finding
// the k-th largest or smallest elements in a collection.
// Here, we will implement a max heap.
// We can change it to min heap by changing the sign in three places marked below.
// Time Complexity:
// Insertion: O(log n)
// Deletion: O(log n)
// Peek: O(1)
// Space Complexity: O(n)
// where n is the number of elements in the heap.
public class Heaps {

    static class Heap {

        ArrayList<Integer> arr = new ArrayList<>();

        public void add(int data) {
            // add at last index
            arr.add(data); // [11, 10, 8, 9, 6, 7, 4, 5, 2, 3]


            int x = arr.size() - 1; // index of last element // x = 10 - 1 = 9
            int par = (x - 1) / 2; // index of parent element // parent index formula // 9-1 / 2 = 4
            // arr.get(x) = 3
            // arr.get(par) = 6
            // now we will do
            // compare the newly added element with its parent and if it is greater than its parent we will swap them.
            // we will continue this process until the newly added element is less than or equal to its parent or it becomes the root of the heap.

            // up-heapify
            // T.C log(n)

            // (1) if we change the sign below to make it accending order 
            // up-heapify means to move the newly added element up the heap until the heap property is restored.
            // means we will compare the newly added element with its parent and if it is greater than its parent we will swap them.
            // we will continue this process until the newly added element is less than or equal to its parent or it becomes the root of the heap.
            // example :
            //         10
            //        /  \
            //       9    8
            //      / \
            //     7   6
            //    / \
            //   5   4
            //  / \
            // 3   2
            // if we add 11 to the heap it will be added at the last index and then we will compare it with its parent 5 and swap them.
            // then we will compare 11 with its new parent 7 and swap them.
            // then we will compare 11 with its new parent 9 and swap them.
            // finally we will compare 11 with its new parent 10 and swap them.
            // now 11 is the root of the heap and the heap property is restored.
            // thus the final heap will be:
            //         11
            //        /  \
            //       10   8
            //      / \
            //     9   6
            //    / \
            //   7   4
            //  / \
            // 5   2
            // thus the time complexity of insertion is O(log n) where n is the number of elements in the heap.
            // It's min or max heap? 
            // Here it is max heap as parent is always greater than child.
            // For min heap just change the sign from > to < in the while condition.
            // Similarly, in heapify function change the signs accordingly.
            // like in if conditions change > to < and < to >.
            // This will make it min heap.
            // example of min heap:
            //         2
            //        /  \
            //       3    4
            //      / \
            //     5   6
            //    / \
            //   7   8
            //  / \
            // 9   10
            // if we add 1 to the heap it will be added at the last index and then we will compare it with its parent 9 and swap them.
            // then we will compare 1 with its new parent 7 and swap them.
            // then we will compare 1 with its new parent 5 and swap them.
            // then we will compare 1 with its new parent 3 and swap them.
            // finally we will compare 1 with its new parent 2 and swap them.
            // now 1 is the root of the heap and the heap property is restored.
            // thus the final heap will be:
            //         1
            //        /  \
            //       2    4
            //      / \
            //     3   6
            //    / \
            //   5   8
            //  / \
            // 7   10
            // thus the time complexity of insertion is O(log n) where n is the number of elements in the heap.
            // To add we don't need to call heapify function as we are adding at last and then up-heapifying.
            // heapify is called when we remove the root element and replace it with the last element.
            // then we need to down-heapify the root element to restore the heap property.
            // we will see that in remove function.
            while (arr.get(x) > arr.get(par)) { // T.C log(n) // (1) if we change the sign here to make it accending order
                // value of arr.get(x) = 11 
                // value of arr.get(par) = 5
                // 11 > 5  true
                // value of arr.get(x) = 11
                // value of arr.get(par) = 7
                // 11 > 7 true
                // value of arr.get(x) = 11
                // value of arr.get(par) = 9
                // 11 > 9 true
                // value of arr.get(x) = 11
                // value of arr.get(par) = 10
                // 11 > 10 true
                // value of arr.get(x) = 11
                // value of arr.get(par) = NA (as x=0 now)
                // loop ends
                // where u taken values from?
                // like adding value will be like [11,10,8,9,6,7,4,5,2,3]
                // what if only one element is there?
                // then arr.get(x) and arr.get(par) will be same
                // so 11 > 11 false
                // loop ends
                // what if two elements are there?
                // then arr.get(x) = 10 and arr.get(par) = 11
                // so 10 > 11 false
                // loop ends
                // what if three elements are there?
                // then arr.get(x) = 8 and arr.get(par) = 11
                // so 8 > 11 false
                // loop ends
                // give one true example?
                // like adding 15 now
                // then arr.get(x) = 15 and arr.get(par) = 11
                // so 15 > 11 true
                // loop continues
                // value of arr.get(x) = 15
                // value of arr.get(par) = 10
                // 15 > 10 true
                // loop continues
                // value of arr.get(x) = 15
                // value of arr.get(par) = 9
                // (x - 1) / 2; how it's calculated? give example with 11 values
                // so index of 15 is 10
                // so par = (10 - 1) / 2 = 4
                // so arr.get(par) = 6
                // 15 > 6 true
                // loop continues

                // swap
                int temp = arr.get(x);
                arr.set(x, arr.get(par));
                arr.set(par, temp);

                //updating the values

                x = par;
                par = (x-1)/2;
            }
        }

        // to see the last element
        public int peek() {
            return arr.get(0);
        }

        private void heapify(int i) {
            int left = 2 * i + 1;
            int right = 2 * i + 2;
            int minIdx = i; // considering it as a min indx

            // rearringing the root, left child, and right child

            // also check weather our left child or right chile exist or not
            if (left < arr.size() && arr.get(minIdx) < arr.get(left)) { // (2) if we change the sign here to make it accending order
                minIdx = left;
            }

            if (right < arr.size() && arr.get(minIdx) < arr.get(right)) {// (3) if we change the sign here to make it accending order
                minIdx = right;
            }

            if (minIdx != i) {

                // swap
                int temp = arr.get(i);
                arr.set(i, arr.get(minIdx));
                arr.set(minIdx, temp);

                // now if the below tree also got mixed up so

                heapify(minIdx);
            }

        } 

        // to remove form heap
        // removing minimum element

        public int remove() {
            int data = arr.get(0);

            // step 1 swap 1st element and last element
            int temp = arr.get(0);
            arr.set(0, arr.get(arr.size() - 1));
            arr.set(arr.size() - 1, temp);

            // step 2 delete the last node
            arr.remove(arr.size() - 1);

            // step 3 fix the heap
            heapify(0);

            return data;

        }

        public boolean isEmpty() {

            return arr.size() == 0;
        }

    }

    public static void main(String args[]) {

        Heap h = new Heap();

        h.add(3);
        h.add(4);
        h.add(1);
        h.add(5);
        h.add(2);
        

        while(!h.isEmpty()){
            System.out.print(h.peek());
            h.remove();
        }
    }

}