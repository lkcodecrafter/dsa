import java.util.*;
public class Iteration_hashset {
    public static void main(String args[]){
        HashSet<Integer> hs = new HashSet<>();

        hs.add(1);
        hs.add(2);
        hs.add(3);
        hs.add(4);

        Iterator it = hs.iterator();
        while(it.hasNext()){
            System.out.print(it.next()+" ");
        }
        System.out.println();
        //using advance for loop

        for(Integer i : hs){
            System.out.print(i+" ");
        }
    }
    
}

/*

lkcodecrafter: Can you help me to understand this code and hashset functions 

GitHub Copilot: Certainly! Here’s a brief explanation of your code and the main HashSet functions:

### Code Explanation
- You import `java.util.*` to use Java collections.
- You create a `HashSet<Integer>` called `hs` and add integers 1, 2, 3, and 4.
- You iterate over the HashSet using:
  1. An `Iterator` (`it.hasNext()` and `it.next()`).
  2. An enhanced for loop (`for(Integer i : hs)`).
- Both loops print each element in the HashSet.

### HashSet Functions Used
- `add(element)`: Adds an element to the HashSet.
- `iterator()`: Returns an iterator to traverse the HashSet.
- `hasNext()`: Checks if there are more elements in the iterator.
- `next()`: Gets the next element from the iterator.

### About HashSet
- HashSet stores unique elements (no duplicates).
- It does not guarantee any order of elements.
- Common functions:
  - `add(E e)`: Adds element.
  - `remove(Object o)`: Removes element.
  - `contains(Object o)`: Checks if element exists.
  - `size()`: Returns number of elements.
  - `isEmpty()`: Checks if empty.
  - `clear()`: Removes all elements.

Let me know if you want examples of other HashSet methods or a deeper explanation!

*/