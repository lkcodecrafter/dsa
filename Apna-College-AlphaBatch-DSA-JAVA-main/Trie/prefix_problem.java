public class prefix_problem {

    static class Node{
        Node[]children = new Node[26];
        boolean eow  = false;
        int freq;

        public Node(){
            for(int i =0; i<children.length; i++){
                children[i] = null;
                freq = 1;
            }
        }
    }

    public static Node root = new Node();

    public static void insert(String word){
        Node curr  = root;
        for(int i =0; i<word.length(); i++){
            int idx = word.charAt(i) -'a';

            if(curr.children[idx] == null){
                curr.children[idx] = new Node();
            }else{
                curr.children[idx].freq++;
            }

            curr = curr.children[idx];
        }

        curr.eow = true;
    }

    public static void findprefix(Node root, String ans){

        if(root == null) return;

        if(root.freq == 1){
            System.out.println(ans);
            return;
        } 

        for(int i =0; i<root.children.length; i++){
            if(root.children[i] != null){
                findprefix(root.children[i], ans+(char)(i+'a'));
            }
        }

    }
    public static void main(String args[]){
        String []arr = {"zebra", "dog", "duck","dove"};

        for(int i = 0; i<arr.length; i++){
            insert(arr[i]);
        }

        root.freq = -1;

        findprefix(root, "");
    }
}


        // what is happening here
        // we are traversing the trie and checking if the frequency of the node is 1
        // if it is 1, then we have found the unique prefix for that word
        // and we print the ans string which contains the prefix
        // if the frequency is not 1, we continue traversing the trie
        // until we find a node with frequency 1
        // Dry run for better understanding
        // for example, for the word "dog" and "dove", the trie will look like this:
        //          root
        //         /    \
        //        d      z
        //       / \
        //      o   u
        //     /     \
        //    g       c
        //   /         \
        //  e           k
        // The unique prefix for "dog" is "do" and for "dove" is "dov"
        // because at the node 'o', the frequency is 2 (for "dog" and "dove")
        // but at the node 'g', the frequency is 1 (only for "dog")
        // and at the node 'e', the frequency is 1 (only for "dove")
        // so we print "do" and "dov" as the unique prefixes
        // similarly for "zebra", the unique prefix is "z" because at the node 'z', the frequency is 1
        // so we print "z" as the unique prefix
        // This is how the algorithm works
        // But we print g and v instead of do and dov
        // because we are printing the ans string when we reach the node with frequency 1
        // so the ans string contains the prefix up to that node
        // Hence the output will be:
        // z
        // dog
        // duck
        // dove

        // my out are 
        // dog
        // dov
        // du
        // z
        // how? above are my dry run notes
        // because we are printing the ans string when we reach the node with frequency 1
        // so the ans string contains the prefix up to that node

/*
Purpose

This method prints the shortest unique prefix for words stored in a Trie.

freq → number of words passing through that node

If freq == 1, the prefix is unique → print it and stop exploring further

ans → prefix formed so far

Assumed input (Trie built from these words)
dog
dove
duck

Trie structure (with freq)
(root)
  |
  d (freq=3)
  |
  o (freq=2)        u (freq=1)
  |                 |
  g (1)  v (1)      c (1)
         |
         e (1)

Initial call
findprefix(root, "");

Dry Run Step-by-Step
1️⃣ At root

root.freq ≠ 1

Loop over children

Child 'd' exists

Call:

findprefix(node('d'), "d")

2️⃣ At node 'd'

freq = 3 → not unique

Loop children: 'o', 'u'

3️⃣ Go to 'o'

Call:

findprefix(node('o'), "do")


freq = 2 → not unique

Loop children: 'g', 'v'

4️⃣ Go to 'g'

Call:

findprefix(node('g'), "dog")


freq = 1 ✅

Print:

dog


Return

5️⃣ Back to 'o', go to 'v'

Call:

findprefix(node('v'), "dov")


freq = 1 ✅

Print:

dov


Return

6️⃣ Back to 'd', go to 'u'

Call:

findprefix(node('u'), "du")


freq = 1 ✅

Print:

du


Return

✅ Final Output
dog
dov
du

Key Takeaways

The function performs a DFS traversal of the Trie

It stops recursion as soon as a unique prefix (freq == 1) is found

ans builds the prefix character by character

Time complexity: O(total characters in trie)


Not all dog — it prints only the prefix built so far, which happens to be "dog" in this case.

Let me explain clearly 👇

Key line in your code
if (root.freq == 1) {
    System.out.println(ans);
    return;
}

What this means

When the current node’s freq becomes 1

The string stored in ans is already unique

So the function prints ans and stops going deeper

In the case of "dog"

Traversal path:

d → o → g

Node	freq	ans	Printed?
d	3	"d"	❌
o	2	"do"	❌
g	1	"dog"	✅

✔ Since g.freq == 1, "dog" is the shortest unique prefix
So it prints:

dog

Important clarification
❌ It does NOT mean:

“Print the whole word because g is last”

✅ It means:

“Print whatever prefix we have reached when freq becomes 1”

Example where it prints before end of word

Words:

zebra
dog
duck

Trie path for "duck":
d (2) → u (1) → c → k


At node 'u':

ans = "du"
freq = 1


Output:

du


Even though the full word is "duck", it prints "du", not "duck".

Final rule

🔹 The function prints the shortest prefix where freq == 1
🔹 That prefix may or may not be the full word

*/