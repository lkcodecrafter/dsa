import java.util.*;

/* ## 6. Adapter

** Intent:** Convert one interface to another.  converting one interface into another so
             they can work together without changing either original device.
*/

interface Payment {
    public void pay(int amount);
}

class PhonePe {
    public void makePayment(int amount) {
        System.out.println("Payment using phone pe with amount of Rs : " + amount);
    }
}

class PhonePayAdapter implements Payment {

    PhonePe phonePe;

    PhonePayAdapter(PhonePe phonePe) {
        this.phonePe = phonePe;
    }

    @Override
    public void pay(int amount) {
        phonePe.makePayment(amount);
    }
}

class AdapterPattern {
    public static void main(String[] args) {
        Payment payment = new PhonePayAdapter(new PhonePe());
        payment.pay(100);

    }
}