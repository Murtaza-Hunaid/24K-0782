#include <iostream>
using namespace std;

class Student
{
    int studentId;
    string name;
    int age;
    char grade;

public:
    Student() {
        grade = 'N'; 
    }

    Student(int studentId, string name, int age, char grade) {
        this->studentId = studentId;
        this->name = name;
        this->age = age;
        this->grade = grade;
    }

    void promoteStudent() {
        if (grade == 'A') {
            cout << "Cannot be further promoted. Already achieved highest grade." << endl;
            return; }
        grade -= 1;
    }

    bool isEligibleForScholarship() {
        if (grade == 'A') {
            return true; }
        else {
            return false; }
    }

    void displayDetails() {
        cout << "Student ID: " << studentId << endl;
        cout << "Name: " << name << endl;
        cout << "Age: " << age << endl;
        cout << "Grade: " << grade << endl;
    }
};

int main()
{
    int n, id, age;
    string name;
    char grade;
    cout << "Enter the number of students: ";
    cin >> n;
    Student *students = new Student[n];
    for (int i = 0; i < n; i++) {
        cout << "Enter the student ID of student " << (i + 1) << ": ";
        cin >> id;
        cin.ignore();
        cout << "Enter the name of student " << (i + 1) << ": ";
        getline(cin, name);
        cout << "Enter the age of student " << (i + 1) << ": ";
        cin >> age;
        cout << "Enter the grade of student " << (i + 1) << ": ";
        cin >> grade;
        students[i] = Student(id, name, age, grade); }
    for (int i = 0; i < n; i++) {
        cout << endl
             << "Displaying details before upgrading the grade of student " << (i + 1) << ": " << endl;
        (students + i)->displayDetails();
        (students + i)->promoteStudent();
        cout << endl << "Displaying details after upgrading the grade of student " << (i + 1) << ": " << endl;
        (students + i)->displayDetails();
        if ((students + i)->isEligibleForScholarship()) {
            cout << "Student " << (i + 1) << " is eligible for scholarship." << endl; }
        else {
            cout << "Student " << (i + 1) << " is not eligible for scholarship." << endl; } }
    delete[] students;
    return 0;
}
