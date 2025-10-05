import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.*;
 
class GroupAnagrams{
        public  List<List<String>> groupAnagrams(String[] strs){
        HashMap<String, List<String>>mp = new HashMap();
        for(String word : strs){
            char[] c = word.toCharArray();
            Arrays.sort(c);
            String s = new String(c);
            if(!mp.containsKey(s)){
                mp.put(s, new ArrayList<>());
            }
            mp.get(s).add(word);
        }
        return new ArrayList<>(mp.values());
    }

public static void main(String[] args) {
        GroupAnagrams solution = new GroupAnagrams();
        String[] input = {"eat", "tea", "tan", "ate", "nat", "bat"};
        List<List<String>> result = solution.groupAnagrams(input);
        System.out.println(result);
}

}