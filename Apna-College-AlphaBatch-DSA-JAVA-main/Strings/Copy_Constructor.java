public class Copy_Constructor{

    public static void main(String args[]){

        Student s1 = new Student();
            s1.name = "abcd";
            s1.roll = 42;
            s1.pwd = "0000";

            // Copy Constuctor 

            Student s2 = new Student(s1);
        // copying everything excepet password
            s2.pwd = "9999";


        System.out.println(s2.toString());


    }
    
}

class Student{

    String name;
    int roll;
    String pwd;

    // function for copy constructor

    Student(Student s1){

        this.name = s1.name;
        this.roll = s1.roll;

    }

    Student(){
        System.out.println("Constructor called");
    }

    public String toString(){
        return this.name+" "+this.roll+" "+this.pwd;
    }
    
}
