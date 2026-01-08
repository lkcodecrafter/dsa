public class lexicographic_order {

    public static void main(String args[]) {

        String fruit[]  = {"banana","apple","mango"};

        String largest = fruit[0];

        for(int i= 0; i<fruit.length; i++){

            // compareTo() method
            // if return value is greater than 0, then the string is lexicographically larger
            // if return value is less than 0, then the string is lexicographically smaller
            // if return value is equal to 0, then the strings are equal
            // eg: mango compareTo apple = positive value
            //     apple compareTo mango = negative value
            //    apple compareTo apple = 0
            // thus we are checking for positive value
            // to find the largest string
            // banana compareTo apple = positive value than returns largest as banana
            // mango compareTo banana = positive value than returns largest as mango

            if(fruit[i].compareTo(largest) > 0){

                largest = fruit[i];

            }

        }

        System.out.println(largest);
    }
    
}
