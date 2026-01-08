public class vovels_count {

    public static void count(String str){
        
        int count = 0;
        for(int i =0; i <str.length(); i++){
            if(str.charAt(i) != Character.toUpperCase(str.charAt(i))){
                count ++;
            }
        }

        System.out.println(count);

    }

    public static void main(String args[]){
        String str = "MAGhhghJKJ";
        // Dry Run
        // M A G h h g h J K J
        // 0 0 0 1 2 3 4 4 4 4
        // final count = 4
        count(str);

    }
    
}
