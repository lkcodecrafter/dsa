import java.util.*;

// ## 8. Composite
// **Intent:** Tree structure.

interface Employee {
    void showEmpDetails();
}

class Developer implements Employee {

    private String name;

    Developer(String name) {
        this.name = name;
    }

    @Override
    public void showEmpDetails() {
        System.out.println("Developer : " + name);
    }
}

class Manager implements Employee {

    private String name;

    private List<Employee> employees = new ArrayList<>();

    public Manager(String name) {
        this.name = name;
    }

    public void add(Employee emp) {
        employees.add(emp);
    }

    public void remove(Employee emp) {
        employees.remove(emp);
    }

    @Override
    public void showEmpDetails() {
        System.out.println("Manager : " + name);

        for (Employee emp : employees)
            emp.showEmpDetails();
    }
}

class CompositePattern {
    public static void main(String[] args) {

        Developer dev1 = new Developer("John");
        Developer dev2 = new Developer("Jane");

        Manager manager = new Manager("Bob");
        manager.addEmp(dev1);
        manager.addEmp(dev2);

        manager.showEmpDetails();

    }
}