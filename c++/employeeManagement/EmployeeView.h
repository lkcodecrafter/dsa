#pragma once

#include "EmployeeViewModel.h"

class EmployeeView {

private:

    EmployeeViewModel* viewModel;

public:

    EmployeeView(EmployeeViewModel* vm);

    void menu();
};
