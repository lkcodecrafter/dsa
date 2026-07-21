import java.util.*;

/*

## 13. Chain of Responsibility Pattern
Definition

The Chain of Responsibility (CoR) pattern allows a request to pass through a chain of objects until one of them handles it.

Instead of the sender knowing who will process the request, it simply sends it to the first object in the chain.

Think of it as:

"If I can't handle it, I'll pass it to the next person."

*/

abstract class Approver {

    private Approver next;

    abstract void approve(int amount);

    void setNext(Approver nxt) {
        this.next = nxt;
    }

    protected void forward(int amount) {
        if (next != null) {
            next.approve(amount);
        } else {
            System.out.println("No approver found.");
        }
    }
}

class TeamLead extends Approver {
    @Override
    void approve(int amount) {
        if (amount <= 3000) {
            System.out.println("Team Lead approved ₹ " + amount);
        } else {
            forward(amount);
        }
    }
}

class Manager extends Approver {

    @Override
    void approve(int amount) {
        if (amount <= 10000) {
            System.out.println("Manager approved ₹ " + amount);
        } else {
            forward(amount);
        }
    }
}

class HOD extends Approver {
    @Override
    void approve(int amount) {
        System.out.println("Director approved ₹ " + amount);
    }
}

class ChainofResponsibilityPattern {

    public static void main(String[] args) {
        Approver teamLead = new TeamLead();
        Approver manager = new Manager();
        Approver hod = new HOD();

        teamLead.setNext(manager);
        manager.setNext(hod);

        teamLead.approve(3000);
        teamLead.approve(11000);
        teamLead.approve(20000);
    }
}