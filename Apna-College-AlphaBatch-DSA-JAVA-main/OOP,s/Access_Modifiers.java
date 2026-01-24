public class Access_Modifiers {

    public static void main(String args[]){

        BankAcc myacc = new BankAcc();

        //public class
        System.out.println(myacc.name);

        //private class therefore it is showing error

       /* System.out.println(myacc.atmPin); */ 

        //but we can change the elements of private class by using a public function made to change it 

        myacc.setPin(9999);
    }
    
}

class BankAcc{

    //Access modifers
    //1. public
    //2. private
    //3. protected
    //4. default
    // private can only be accessed within the class
    // public can be accessed from anywhere
    // protected can be accessed within the package and also outside the package by child class
    // default can be accessed only within the package
    // if no access modifer is specified it is considered as default
    private int atmPin = 1234;
    public String name = "mandar";

    public void setPin(int newPin){
        atmPin = newPin;

    }
    public void getPin(){
        System.out.println(atmPin);
    }

    // Give me example of protected and default access modifers
    // protected int accNumber = 56789;
    // String bankName = "ABC Bank";
    // default access modifer
    // void displayBankInfo(){
    //     System.out.println("Bank Name: " + bankName);
    // }
    // protected void displayAccNumber(){
    //     System.out.println("Account Number: " + accNumber);
    // }
    

}
