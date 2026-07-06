# Employee Management C++ Project - Build & Run Guide

## Prerequisites
- Install [CMake](https://cmake.org/download/) and add it to your system PATH.
- Install a C++ compiler (MSYS2 g++ recommended for Windows).
- (Optional) Use Visual Studio Code for easy terminal and editing.

## Project Structure
- `main.cpp`, `EmployeeView.cpp`, `EmployeeViewModel.cpp`, etc. (source files)
- `CMakeLists.txt` (build configuration)
- `build/` (build output directory)

## Step-by-Step Build & Run Instructions

### 1. Open Terminal in Project Folder
- In VS Code: `View` → `Terminal` or press `Ctrl + ``
- Make sure you are in the `employeeManagement` folder.

### 2. Create a Build Directory
```powershell
mkdir build
cd build
```

### 3. Generate Build Files with CMake
```powershell
cmake ..
```
- This creates build files in the `build` directory.

### 4. Compile the Project
```powershell
cmake --build .
```
- This creates `employeeManagement.exe` in the `build` folder.

### 5. Run the Program
```powershell
.\employeeManagement.exe
```
- The employee management menu will appear.

## Notes
- If you add new `.cpp` files, just re-run steps 4 and 5.
- If you get a 'cmake not recognized' error, install CMake and restart your terminal.
- You can also build manually (not recommended for larger projects):
  ```powershell
  g++ -g main.cpp EmployeeView.cpp EmployeeViewModel.cpp -o employeeManagement.exe
  .\employeeManagement.exe
  ```

---
Feel free to ask for help if you get stuck!
