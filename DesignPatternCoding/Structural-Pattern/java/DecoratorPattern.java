import java.util.*;

// ## 9. Decorator
// **Intent:** Add responsibilities dynamically.

interface Coffee {
    String getDescription();

    int getCost();
}

// Base Coffee
class SimpleCoffee implements Coffee {
    @Override
    public String getDescription() {
        return "Simple Coffee";
    }

    @Override
    public int getCost() {
        return 50;
    }
}

// Decorator Base
abstract class CoffeeDecorator implements Coffee {
    protected Coffee decoratedCoffee;

    CoffeeDecorator(Coffee decoratedCoffee) {
        this.decoratedCoffee = decoratedCoffee;
    }

    @Override
    public String getDescription() {
        return decoratedCoffee.getDescription();
    }

    @Override
    public int getCost() {
        return decoratedCoffee.getCost();
    }
}

// Concrete Decorators
class MilkDecorator extends CoffeeDecorator {
    MilkDecorator(Coffee decoratedCoffee) {
        super(decoratedCoffee);
    }

    @Override
    public String getDescription() {
        return decoratedCoffee.getDescription() + ", with Milk";
    }

    @Override
    public int getCost() {
        return decoratedCoffee.getCost() + 20;
    }
}

class SugarDecorator extends CoffeeDecorator {
    SugarDecorator(Coffee decoratedCoffee) {
        super(decoratedCoffee);
    }

    @Override
    public String getDescription() {
        return decoratedCoffee.getDescription() + ", with Sugar";
    }

    @Override
    public int getCost() {
        return decoratedCoffee.getCost() + 10;
    }
}

public class DecoratorPattern {
    public static void main(String[] args) {
        // 1. Simple Coffee
        Coffee c1 = new SimpleCoffee();
        System.out.println(c1.getDescription() + " -> Cost: " + c1.getCost());

        // 2. Coffee with Milk
        Coffee c2 = new MilkDecorator(new SimpleCoffee());
        System.out.println(c2.getDescription() + " -> Cost: " + c2.getCost());

        // 3. Coffee with Milk + Sugar (Chaining)
        Coffee c3 = new SugarDecorator(new MilkDecorator(new SimpleCoffee()));
        System.out.println(c3.getDescription() + " -> Cost: " + c3.getCost());
    }
}