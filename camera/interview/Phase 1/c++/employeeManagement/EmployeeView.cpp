#include <iostream>
#include "EmployeeView.h"

using namespace std;

EmployeeView::EmployeeView(EmployeeViewModel* vm) {

    viewModel = vm;
}

void EmployeeView::menu() {

    int choice;

    while (true) {

        cout << "\n===== Employee App =====\n";

        cout << "1. Add Employee\n";
        cout << "2. Show Employees\n";
        cout << "3. Search Employee\n";
        cout << "4. Exit\n";

        cout << "Enter Choice: ";
        cin >> choice;

        if (choice == 1) {

            int id;
            string name;
            int salary;

            cout << "Enter ID: ";
            cin >> id;

            cout << "Enter Name: ";
            cin >> name;

            cout << "Enter Salary: ";
            cin >> salary;

            viewModel->addEmployee(id, name, salary);
        }
        else if (choice == 2) {

            viewModel->displayEmployees();
        }
        else if (choice == 3) {

            int id;

            cout << "Enter Employee ID: ";
            cin >> id;

            viewModel->searchEmployee(id);
        }
        else if (choice == 4) {

            cout << "Exiting Application...\n";
            break;
        }
        else {

            cout << "Invalid Choice\n";
        }
    }
}
