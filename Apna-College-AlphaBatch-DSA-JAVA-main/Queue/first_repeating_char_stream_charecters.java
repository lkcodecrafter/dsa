import java.util.*;

public class first_repeating_char_stream_charecters {

    public static void work(String str) {

        // for storing the frequency of charecters
        int freq[] = new int[26]; // a - z
        Queue<Character> q = new LinkedList<>();

        for (int i = 0; i < str.length(); i++) {

            char ch = str.charAt(i); // getting each charecter like a,a,b,c,c,x,b
            q.add(ch);  // adding charecter to the queue like a,a,b,c,c,x,b

            // increasing freq of that number
            /*
             * if charecter is a the a-a = 0 so index at a will increase
             * and for example ch = c the c-a = 99-97 = 2 so the index 2 will increase
             */

            freq[ch - 'a']++; // increasing the freq of that charecter like a=2,b=2,c=2,x=1

            while (!q.isEmpty() && freq[q.peek() - 'a'] > 1) { // what is condition
                // removing the charecters from the queue whose freq is more than 1
                // like a=2 so removing a,b=2 so removing b,c=2 so removing c
                // finally x=1 so stop removing
                q.remove();

            }
            if (q.isEmpty()) {
                System.out.print("-1 ");
            } else {
                // output the first non repeating charecter
                // like x
                // but it's printing a -1 b b b b x 
                // because after removing a,b,c the first non repeating charecter is x
                // but in the previous stream a is also non repeating so it's printing a also
                // so final output is a -1 b b b b x
                // how to fix it
                // we have to print the first non repeating charecter at each step of stream
                // so we are printing q.peek() at each step
                // like a -1 b b b b x
                // which is correct
                // i think out is x only once
                // but we have to print at each step of stream
                // so final output is a -1 b b b b x
                // b b b b printing b multiple times because after removing a,b,c the first non repeating charecter is b
                // so it's printing b multiple times until a new non repeating charecter comes
                // peek means first element of the queue
                // like b is at front of the queue
                // so it's printing b multiple times
                // how can i print only x   
                // but the question is to print at each step of stream
                // so final output is correct
                // but i want only x
                // so we have to change the question
                // question is to print the first non repeating charecter at each step of stream
                System.out.print(q.peek() + " ");
            }

        }

    }

    public static void printOnlyUniqueOnce(String str) {
        int freq[] = new int[26];
        Queue<Character> q = new LinkedList<>();
        Set<Character> printed = new HashSet<>();

        for (int i = 0; i < str.length(); i++) {
            char ch = str.charAt(i);
            q.add(ch);
            freq[ch - 'a']++;

            while (!q.isEmpty() && freq[q.peek() - 'a'] > 1) {
                q.remove();
            }

            if (!q.isEmpty() && !printed.contains(q.peek())) {
                System.out.print(q.peek() + " ");
                printed.add(q.peek()); // output only once like x
                // out is a b x why
                // because a is first non repeating charecter
                // then b is first non repeating charecter
                // then x is first non repeating charecter
                // so final output is a b x
            }
        }
    }

    public static void main(String args[]) {
        String str = "aabccxb";
        printOnlyUniqueOnce(str);
        System.out.println();
        work(str);

    }

}
