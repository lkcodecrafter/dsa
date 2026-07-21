import java.util.*;

/*

14. Command Pattern

Intent : Encapsulate a request as an object, thereby letting you parameterize methods 
        with different requests, queue or log requests, and support undoable operations.


*/

/**
 * InnerCommandPattern
 */
public interface Command {
    void execute();

    void undo();
}

class Light {

    public void lightOn() {
        System.out.println("Light is on ");
    }

    public void lightOff() {
        System.out.println("Light is off ");
    }

}

class LightOnCommand implements Command {

    private Light light;

    LightOnCommand(Light light) {
        this.light = light;
    }

    @Override
    public void execute() {
        light.lightOn();
    }

    @Override
    public void undo() {
        light.lightOff();
    }
}

class LightOffCommand implements Command {

    private Light light;

    LightOffCommand(Light light) {
        this.light = light;
    }

    @Override
    public void execute() {
        light.lightOff();
    }

    @Override
    public void undo() {
        light.lightOn();
    }
}

class Remote {
    private Command command;

    public void setCommand(Command command) {
        this.command = command;
    }

    public void buttonClicked() {
        command.execute();
    }

    public void undo() {
        if (command != null)
            command.undo();
    }
}

class CommandPattern {
    public static void main(String[] args) {

        Light light = new Light();
        LightOnCommand lightOnCommand = new LightOnCommand(light);
        LightOffCommand lightOffCommand = new LightOffCommand(light);
        Remote remote = new Remote();
        remote.setCommand(lightOnCommand);
        remote.buttonClicked();
        remote.setCommand(lightOffCommand);
        remote.buttonClicked();
        remote.setCommand(lightOnCommand);
        remote.buttonClicked();
        remote.undo();

    }
}