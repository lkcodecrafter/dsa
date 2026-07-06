
#include <iostream>
#include <vector>
using namespace std;

struct Student {
    int id;
    string name;
    float marks;
};

int main() {
    vector<Student> students;

    while (true) {
        int choice;
        cout << "\n1.Add 2.Display 3.Exit : ";
        cin >> choice;

        if (choice == 1) {
            Student s;
            cout << "ID: ";
            cin >> s.id;
            cout << "Name: ";
            cin >> s.name;
            cout << "Marks: ";
            cin >> s.marks;
            students.push_back(s);
        }
        else if (choice == 2) {
            for (auto &s : students) {
                Student* ptr = &s;
                cout << ptr->id << " "
                     << ptr->name << " "
                     << ptr->marks << endl;
            }
        }
        else {
            break;
        }
    }
    return 0;
}
