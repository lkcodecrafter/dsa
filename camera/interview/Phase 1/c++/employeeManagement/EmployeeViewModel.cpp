#include <iostream>
#include "EmployeeViewModel.h"

using namespace std;

void EmployeeViewModel::addEmployee(int id, string name, int salary) {

    Employee* emp = new Employee();

    emp->id = id;
    emp->name = name;
    emp->salary = salary;

    employees.push_back(emp);

    cout << "Employee Added Successfully\n";
}

void EmployeeViewModel::displayEmployees() {

    if (employees.empty()) {

        cout << "No Employees Found\n";
        return;
    }

    cout << "\nEmployee List\n";

    for (Employee* emp : employees) {

        cout << "-------------------\n";

        cout << "ID     : " << emp->id << endl;
        cout << "Name   : " << emp->name << endl;
        cout << "Salary : " << emp->salary << endl;
    }
}

void EmployeeViewModel::searchEmployee(int id) {

    for (Employee* emp : employees) {

        if (emp->id == id) {

            cout << "\nEmployee Found\n";

            cout << "ID     : " << emp->id << endl;
            cout << "Name   : " << emp->name << endl;
            cout << "Salary : " << emp->salary << endl;

            return;
        }
    }

    cout << "Employee Not Found\n";
}

EmployeeViewModel::~EmployeeViewModel() {

    cout << "\nCleaning Heap Memory...\n";

    for (Employee* emp : employees) {

        delete emp;
    }

    employees.clear();
}
