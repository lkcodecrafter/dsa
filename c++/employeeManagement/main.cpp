#include "EmployeeView.h"

int main() {

    EmployeeViewModel* vm = new EmployeeViewModel();

    EmployeeView view(vm);

    view.menu();

    delete vm;

    vm = NULL;

    return 0;
}


// g++ -g main.cpp EmployeeView.cpp EmployeeViewModel.cpp -o employeeManagement.exe