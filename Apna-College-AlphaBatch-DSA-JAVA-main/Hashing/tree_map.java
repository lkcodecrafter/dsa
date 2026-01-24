import java.util.*;
public class tree_map {
    public static void main(String args[]){
        TreeMap<String,Integer> tm = new TreeMap<>();

        tm.put("b",1);
        tm.put("c",2);
        tm.put("a",3);
        tm.put("d",1);

        HashMap<String,Integer> hm = new HashMap<>();

        hm.put("a",1);
        hm.put("b",2);
        hm.put("c",3);
        hm.put("d",1);

        //here we can compare the difference in order
        System.out.println(tm);
        System.out.println(hm);
    }
}
/*


### TreeMap vs HashMap vs HashSet

- **TreeMap**
  - Stores key-value pairs (like a dictionary).
  - Keys are sorted in natural order (e.g., alphabetical for strings).
  - Slower than HashMap for most operations (O(log n)).
  - Example: `{a=3, b=1, c=2, d=1}` (always sorted by key).

- **HashMap**
  - Stores key-value pairs.
  - No order is guaranteed for keys.
  - Fast operations (O(1) average).
  - Example: `{a=1, b=2, c=3, d=1}` (order can vary).

- **HashSet**
  - Stores unique values (no key-value pairs).
  - No order is guaranteed.
  - Fast operations (O(1) average).
  - Example: `[a, b, c, d]` (order can vary).

### Your Code Explanation

```java
TreeMap<String,Integer> tm = new TreeMap<>();
tm.put("b",1);
tm.put("c",2);
tm.put("a",3);
tm.put("d",1);

HashMap<String,Integer> hm = new HashMap<>();
hm.put("a",1);
hm.put("b",2);
hm.put("c",3);
hm.put("d",1);

System.out.println(tm); // Output: {a=3, b=1, c=2, d=1} (sorted by key)
System.out.println(hm); // Output: {a=1, b=2, c=3, d=1} (order not guaranteed)
```

- You create a `TreeMap` and a `HashMap`, add the same keys but in different orders.
- When printed, `TreeMap` always shows keys sorted, while `HashMap` shows them in an unpredictable order.
- This demonstrates the main difference: ordering of keys.

Let me know if you want an example for `HashSet` or more details!

Similar code found with 1 license type

*/