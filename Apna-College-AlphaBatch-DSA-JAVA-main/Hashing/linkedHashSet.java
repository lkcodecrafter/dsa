import java.util.*;
public class linkedHashSet {

/*

lkcodecrafter: Can you help me to understand this code also, give diff in all treee set linkedhashset and hashset?

GitHub Copilot: Certainly! Here’s a breakdown of your code and the differences between HashSet, LinkedHashSet, and TreeSet:

### Code Explanation
Your code demonstrates how three different Set implementations in Java work:

1. **HashSet**  
   - Stores elements in no particular order.
   - Fast for add, remove, and contains operations.
   - Output: The numbers will appear in a random order (not sorted, not insertion order).

2. **LinkedHashSet**  
   - Maintains the order in which elements are inserted.
   - Slightly slower than HashSet due to order maintenance.
   - Output: The numbers will appear in the order you added them (3 4 2 1).

3. **TreeSet**  
   - Stores elements in sorted (ascending) order.
   - Slower than HashSet and LinkedHashSet due to sorting.
   - Output: The numbers will appear sorted (1 2 3 4).

### Differences

| Feature         | HashSet         | LinkedHashSet      | TreeSet           |
|-----------------|-----------------|--------------------|-------------------|
| Order           | Unpredictable   | Insertion order    | Sorted order      |
| Performance     | Fastest         | Slightly slower    | Slowest           |
| Nulls allowed   | Yes             | Yes                | No (for natural ordering) |
| Implementation  | Hash Table      | Hash Table + List  | Red-Black Tree    |

### Output Example
Suppose you add 3, 4, 2, 1:
- HashSet: `2 3 1 4` (order may vary)
- LinkedHashSet: `3 4 2 1`
- TreeSet: `1 2 3 4`

Let me know if you want a code comment walkthrough or further details!

*/

    
    public static void main(String args[]){
        
        HashSet <Integer> hs = new HashSet<>();

        hs.add(3);
        hs.add(4);
        hs.add(2);
        hs.add(1);

        for( Integer j:hs){
            System.out.print(j+" ");
        }
        System.out.println();
        
        LinkedHashSet <Integer> lhs = new LinkedHashSet<>();

        lhs.add(3);
        lhs.add(4);
        lhs.add(2);
        lhs.add(1);

        //order is maintained
        for(Integer i: lhs){
            System.out.print(i+" ");
        }
        
        System.out.println();
        System.out.println("Tree set using sorted order");
        //tree set

        TreeSet <Integer> ts = new TreeSet<>();

        ts.add(3);
        ts.add(4);
        ts.add(2);
        ts.add(1);

        //order is maintained
        for(Integer i: ts){
            System.out.print(i+" ");
        }

    }
}
