import java.util.*;
public class LinkedHashMap_java {
    public static void main(String args[]){
        LinkedHashMap<String,Integer> lhm = new LinkedHashMap<>();

        lhm.put("first",1);
        lhm.put("second",2);
        lhm.put("third",3);
        lhm.put("one",1);

        HashMap<String,Integer> hm = new HashMap<>();

        hm.put("first",1);
        hm.put("second",2);
        hm.put("third",3);
        hm.put("one",1);

        //here we can compare the difference in order
        System.out.println(lhm);
        System.out.println(hm);
    }
}

/*


### Difference between HashMap and LinkedHashMap

- **HashMap**:
  - Stores key-value pairs with no guaranteed order.
  - When you iterate over a HashMap, the order of elements is unpredictable.
  - Faster for most operations due to less overhead.

- **LinkedHashMap**:
  - Stores key-value pairs in the order they were inserted.
  - Maintains a doubly-linked list running through all its entries.
  - When you iterate over a LinkedHashMap, elements come out in insertion order.

### Understanding Your Code

In your code:
- You create both a `LinkedHashMap` and a `HashMap`, add the same entries, and print them.
- Output for `LinkedHashMap` will be: `{first=1, second=2, third=3, one=1}` (insertion order).
- Output for `HashMap` could be in any order, e.g., `{one=1, third=3, second=2, first=1}` (order not guaranteed).

### Common Inbuilt Functions

Both `HashMap` and `LinkedHashMap` support these methods:
- `put(key, value)`: Add or update a key-value pair.
- `get(key)`: Retrieve value for a key.
- `remove(key)`: Remove a key-value pair.
- `containsKey(key)`: Check if a key exists.
- `containsValue(value)`: Check if a value exists.
- `size()`: Number of entries.
- `clear()`: Remove all entries.
- `keySet()`, `values()`, `entrySet()`: Get all keys, values, or key-value pairs.

**LinkedHashMap** also supports access-order iteration (not used in your code), which can be useful for implementing LRU caches.

Let me know if you want code examples for any specific function!

*/