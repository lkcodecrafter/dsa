public class creating_Trie {

    static class Node{
        
        Node children[] = new Node [26];
        boolean eow = false;

        Node(){
            for(int i =0; i<26; i++){
                children[i] = null;
            }
        }
    }

    public static Node root = new Node();

    public static void insert(String word){ // T>C = O(L)   length of level
        // what is happening in insert function
        // we are traversing each charecter of the word and checking if that charecter is already present in the trie or not
        // if not present then we are creating a new node for that charecter and moving to the next charecter
        // if present then we are moving to the next charecter
        // at the end we are marking the end of the word by setting eow = true
        // this way we can insert the word in the trie
        // this is done in O(L) time where L is the length of the word
        // space complexity is O(1) as we are not using any extra space
        // only the space required for the trie is used
        // overall space complexity is O(N*L) where N is the number of words and L is the average length of the words
        // Dry run for insert function with word = "the"
        // 1. curr = root
        // 2. level = 0, word.charAt(0) = 't', idx = 't' - 'a' = 19
        // 3. curr.children[19] == null, so we create a new node for 't'
        // 4. curr = curr.children[19]
        // 5. level = 1, word.charAt(1) = 'h', idx = 'h' - 'a' = 7
        // 6. curr.children[7] == null, so we create a new node for 'h'
        // 7. curr = curr.children[7]
        // 8. level = 2, word.charAt(2) = 'e', idx = 'e' - 'a' = 4
        // 9. curr.children[4] == null, so we create a new node for 'e'
        // 10. curr = curr.children[4]
        // 11. level = 3, end of word, so we set curr.eow = true
        // Word "the" inserted in trie
        // similarly we can insert other words
        // end of dry run
        Node curr = root;
        for(int level = 0; level<word.length(); level++){
            int idx = word.charAt(level) - 'a';   // minus a because any charecter - a gives the index of the charecter with 0 based indexing
            if(curr.children[idx] == null){
                curr.children[idx] = new Node();
            }

            curr = curr.children[idx];
        }

        curr.eow = true;
    }

    public static boolean search(String key){

        Node curr = root;
        for(int i =0; i<key.length(); i++){
            int idx = key.charAt(i) - 'a';

            if(curr.children[idx] == null){
                return false;
            }
            curr = curr.children[idx];
        }

        if(curr.eow == true){
            return true;
        }

        return false;
    }
    public static void main(String args[]){
        String words[] = {"the","their","a","their","any","thee"};

        for(int i =0; i<words.length; i++){
            insert(words[i]);
        }

        System.out.println(search("any"));
        System.out.println(search("an"));
    }
}
