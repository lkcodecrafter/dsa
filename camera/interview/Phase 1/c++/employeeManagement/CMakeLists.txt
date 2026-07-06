cmake_minimum_required(VERSION 3.10)
project(employeeManagement)

set(CMAKE_CXX_STANDARD 17)

add_executable(employeeManagement
    main.cpp
    EmployeeView.cpp
    EmployeeViewModel.cpp
)
