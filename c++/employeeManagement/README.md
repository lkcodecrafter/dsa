# C++ MVVM Style Employee Management Project

## Concepts Covered

- Struct
- Pointer
- Dynamic Allocation
- Heap vs Stack
- Vector
- Destructor
- MVVM Style Architecture
- Composition
- Encapsulation

---

# Project Structure

```txt
Employee.h
EmployeeViewModel.h
EmployeeViewModel.cpp
EmployeeView.h
EmployeeView.cpp
main.cpp
```

---

# Architecture

```txt
Model      -> Employee
ViewModel  -> EmployeeViewModel
View       -> EmployeeView
main()     -> Entry Point
```

---

# How To Run In Visual Studio

1. Open Visual Studio
2. Create Empty C++ Console Project
3. Add all .h and .cpp files
4. Build and Run

---

# Features

- Add Employee
- Show Employees
- Search Employee
- Dynamic Memory Handling

---

# Important Learning

## Heap Allocation

```cpp
Employee* emp = new Employee();
```

## Pointer Access

```cpp
emp->id
```

## Destructor Cleanup

```cpp
delete emp;
```

---

# Future Improvements

- Delete Employee
- Update Employee
- File Storage
- Smart Pointers
- Threading
- Mutex
