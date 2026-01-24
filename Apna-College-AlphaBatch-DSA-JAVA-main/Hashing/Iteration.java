import java.util.*;

public class Iteration{
    public static void main(String args[]){

        HashMap <String,Integer> hm = new HashMap<>();

        hm.put("orange",1);
        hm.put("banana",2);
        hm.put("mango",3);
        hm.put("apple",4);

        System.out.println(hm);

        //to iterate we use a set by making a set of keys
        Set<String> keys = hm.keySet();
        //printing the key set

        System.out.println(keys);
        System.out.println();

        for (String k : keys){
            System.out.println("Key ="+k+",value"+hm.get(k));
        }



        
    }
}

/*
lkcodecrafter: Can you help me to understans this code and it's functions

GitHub Copilot: Certainly! Here’s a breakdown of what the code in `Iteration.java` does:

1. **Imports and Setup**:  
   - Imports the `java.util.*` package for using collections like `HashMap` and `Set`.
   - Defines a class `Iteration` with a `main` method.

2. **HashMap Creation**:  
   - Creates a `HashMap<String, Integer>` called `hm`.
   - Adds four key-value pairs to the map: `"orange"`, `"banana"`, `"mango"`, and `"apple"` with integer values.

3. **Printing the HashMap**:  
   - Prints the entire `HashMap` object, which shows all key-value pairs.

4. **Iterating Over Keys**:  
   - Gets the set of keys from the map using `hm.keySet()`.
   - Prints the set of keys.

5. **Iterating and Printing Key-Value Pairs**:  
   - Uses a for-each loop to go through each key in the set.
   - For each key, prints the key and its corresponding value from the map.

**Purpose**:  
This code demonstrates how to store key-value pairs in a `HashMap`, retrieve all keys, and iterate over them to access and print both keys and their values.

If you want a deeper explanation of any part, let me know!

*/