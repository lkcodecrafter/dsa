#pragma once

#include <vector>
#include "Employee.h"

using namespace std;

class EmployeeViewModel {

private:

    vector<Employee*> employees;

public:

    void addEmployee(int id, string name, int salary);

    void displayEmployees();

    void searchEmployee(int id);

    ~EmployeeViewModel();
};
