public class replace {

    public static void main(String args[]) {
        String str = "ApnaCollege";
        str.replace("l", "");
        System.out.println(str);
        // out will be ApnaCollege because string is immutable
        // to store the changes we have to reassign it
        // why immutable -> because it saves memory and makes program efficient
        str = str.replace("l", "");
        System.out.println(str);
    }

}
