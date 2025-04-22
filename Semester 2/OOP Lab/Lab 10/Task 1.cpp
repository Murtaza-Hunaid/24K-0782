#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct Student {
    int id;
    string name;
    float gpa;
};

int main() {
    ofstream outFile("students.txt", ios::out);

    Student students[1];

    for (int i = 0; i < 1; i++) {
        cout << "Enter student " << i + 1 << " ID: ";
        cin >> students[i].id;
        cout << "Enter student " << i + 1 << " Name: ";
        cin.ignore();
        getline(cin, students[i].name);
        cout << "Enter student " << i + 1 << " GPA: ";
        cin >> students[i].gpa;
        outFile << students[i].id << " " << students[i].name << " " << students[i].gpa << endl; }
    outFile.close();

    ofstream appendFile("students.txt", ios::app);
    Student newStudent;
    cout << "Enter additional student ID: ";
    cin >> newStudent.id;
    cout << "Enter additional student Name: ";
    cin.ignore();
    getline(cin, newStudent.name);
    cout << "Enter additional student GPA: ";
    cin >> newStudent.gpa;
    appendFile << newStudent.id << " " << newStudent.name << " " << newStudent.gpa << endl;
    appendFile.close();

    ifstream inFile("students.txt");
    Student readStudent;

    while (inFile >> readStudent.id) {
        inFile >> readStudent.name;
        inFile >> readStudent.gpa;
        cout << "ID: " << readStudent.id << " Name: " << readStudent.name << " GPA: " << readStudent.gpa << endl; }
    inFile.close();

    return 0;

}
