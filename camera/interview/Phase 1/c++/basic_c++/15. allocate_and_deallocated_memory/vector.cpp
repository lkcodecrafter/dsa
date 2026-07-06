#include <iostream>
#include <vector> // Required for std::vector

int main() {
    int n = 5;

    // Create a vector of size 'n' 
    // Memory is automatically allocated and initialized to 0
    std::vector<int> vec(n);

    // Initialize the vector elements
    for (int i = 0; i < n; ++i) {
        vec[i] = (i + 1) * 10;
    }

    // Print the values
    std::cout << "Vector values: ";
    for (int i = 0; i < n; ++i) {
        std::cout << vec[i] << " ";
    }
    std::cout << "\n";

    // Memory is automatically freed when 'vec' goes out of scope here
    return 0;
}
