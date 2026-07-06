import java.util.*;

interface Message {
    public void send(String message);
}

abstract class Notification {
    Message message;

    Notification(Message message) {
        this.message = message;
    }

    public abstract void send(String message);
}

class Sms implements Message {

    @Override
    public void send(String msg) {
        System.out.println("SMS : " + msg);
    }

}

class TwiloSMS implements Message {

    @Override
    public void send(String msg) {
        System.out.println("Twilo SMS : " + msg);
    }
}

class SMSNotification extends Notification {
    SMSNotification(Message message) {
        super(message);
    }

    @Override
    public void send(String msg) {
        message.send(msg);
    }
}

class TwilioSMSNotification extends Notification {
    TwilioSMSNotification(Message message) {
        super(message);
    }

    @Override
    public void send(String msg) {
        message.send(msg);
    }
}

class Bridepattern {
    public static void main(String[] args) {
        Notification sms = new SMSNotification(new Sms());
        sms.send("Hello");

        Notification twiloSMS = new TwilioSMSNotification(new TwiloSMS());
        twiloSMS.send("Hi");
    }
}