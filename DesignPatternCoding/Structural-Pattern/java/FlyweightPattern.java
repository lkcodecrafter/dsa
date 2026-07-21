import java.util.*;

// In Flyweight pattern , the main idea is to share as much as possible with other similar objects
// The flyweight objects are immutable and are stored in a pool
// There are two types of data in a flyweight object
// 1. Intrinsic data: The data that is shared with other objects
// 2. Extrinsic data: The data that is not shared with other objects

interface Shape {
    void draw(int x, int y);
}

class Circle implements Shape {
    private String color;

    Circle(String color) {
        this.color = color;
    }

    @Override
    public void draw(int x, int y) {
        System.out.println("Circle drawn with color " + color + " at coordinates (" + x + ", " + y + ")");
    }
}

class FlyweightFactory {
    private static Map<String, Shape> shapes = new HashMap<>();

    static public Shape getShape(String color) {
        if (!shapes.containsKey(color)) {
            shapes.put(color, new Circle(color));
            System.out.println("Creating new " + color + " Shape");
        }
        return shapes.get(color);
    }
}

class FlyweightPattern {
    public static void main(String[] args) {

        Shape shape = FlyweightFactory.getShape("Red");
        shape.draw(1, 2);

        Shape shape2 = FlyweightFactory.getShape("Blue");
        shape2.draw(3, 4);

        Shape shape3 = FlyweightFactory.getShape("Red");
        shape3.draw(5, 6);

        Shape shape4 = FlyweightFactory.getShape("Green");
        shape4.draw(7, 8);
    }
}