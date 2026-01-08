public class shortest_distance {

    public static float shortest_distance(String path){
        
        int x =0, y = 0;
        for(int i = 0; i< path.length(); i++){
            char direction = path.charAt(i);
            
            // South 
            if(direction == 'S'){
                y--;
            }

            //North
            else if(direction == 'N'){
                y++;
            }

            //East
            else if(direction == 'E'){
                x++;
            }

            //West
            else{
                x--;
            }

        }

        System.out.println("x: "+ x + " y: "+ y);
        int X2 = x*x;
        int Y2 = y*y;

        return (float)Math.sqrt(X2+Y2);
    }
    public static void main(String args[]){
        String path = "WNEENESENNN";

        // Dry run
        // W -> x = -1, y = 0
        // N -> x = -1, y = 1
        // E -> x = 0, y = 1
        // E -> x = 1, y = 1
        // N -> x = 1, y = 2
        // E -> x = 2, y = 2
        // S -> x = 2, y = 1
        // E -> x = 3, y = 1
        // N -> x = 3, y = 2
        // N -> x = 3, y = 3
        // N -> x = 3, y = 4
        // how output is calculated -> sqrt(3^2 + 4^2) = sqrt(9+16) = sqrt(25) = 5
        System.out.print(shortest_distance(path));

    }
    
}
