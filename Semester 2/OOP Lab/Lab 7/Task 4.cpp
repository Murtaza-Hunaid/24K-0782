#include <iostream>
#include <string>

using namespace std;

class Person {
protected:
    string name;
    string id;
    string address;
    string phoneNumber;
    string email;

public:
    Person(string n, string i, string a, string p, string e) : name(n), id(i), address(a), phoneNumber(p), email(e) {}

    virtual void displayInfo() {
        cout << "Name: " << name << endl;
        cout << "ID: " << id << endl;
        cout << "Address: " << address << endl;
        cout << "Phone Number: " << phoneNumber << endl;
        cout << "Email: " << email << endl;
    }

    virtual void updateInfo(string n, string a, string p, string e) {
        name = n;
        address = a;
        phoneNumber = p;
        email = e;
    }

    string getId() {
        return id;
    }
};

class Student : public Person {
private:
    string coursesEnrolled;
    float GPA;
    int enrollmentYear;

public:
    Student(string n, string i, string a, string p, string e, string courses, float g, int year) : Person(n, i, a, p, e), coursesEnrolled(courses), GPA(g), enrollmentYear(year) {}

    void displayInfo() {
        Person::displayInfo();
        cout << "Courses Enrolled: " << coursesEnrolled << endl;
        cout << "GPA: " << GPA << endl;
        cout << "Enrollment Year: " << enrollmentYear << endl;
    }

    void updateInfo(string n, string a, string p, string e, string courses, float g, int year) {
        Person::updateInfo(n, a, p, e);
        coursesEnrolled = courses;
        GPA = g;
        enrollmentYear = year;
    }
};

class Professor : public Person {
private:
    string department;
    string coursesTaught;
    float salary;

public:
    Professor(string n, string i, string a, string p, string e, string dept, string courses, float s) : Person(n, i, a, p, e), department(dept), coursesTaught(courses), salary(s) {}

    void displayInfo() {
        Person::displayInfo();
        cout << "Department: " << department << endl;
        cout << "Courses Taught: " << coursesTaught << endl;
        cout << "Salary: " << salary << endl;
    }

    void updateInfo(string n, string a, string p, string e, string dept, string courses, float s) {
        Person::updateInfo(n, a, p, e);
        department = dept;
        coursesTaught = courses;
        salary = s;
    }
};

class Staff : public Person {
private:
    string department;
    string position;
    float salary;

public:
    Staff(string n, string i, string a, string p, string e, string dept, string pos, float s) : Person(n, i, a, p, e), department(dept), position(pos), salary(s) {}

    void displayInfo() {
        Person::displayInfo();
        cout << "Department: " << department << endl;
        cout << "Position: " << position << endl;
        cout << "Salary: " << salary << endl;
    }

    void updateInfo(string n, string a, string p, string e, string dept, string pos, float s) {
        Person::updateInfo(n, a, p, e);
        department = dept;
        position = pos;
        salary = s;
    }
};

class Course {
private:
    string courseId;
    string courseName;
    int credits;
    string instructor;
    string schedule;

public:
    Course(string id, string name, int c, string instr, string sched) : courseId(id), courseName(name), credits(c), instructor(instr), schedule(sched) {}

    void registerStudent(Student &student) {
        cout << "Student with ID " << student.getId() << " registered for course " << courseId << endl;
    }

    void calculateGrades() {
        cout << "Grades calculated for course " << courseId << endl;
    }

    void displayCourseInfo() {
        cout << "Course ID: " << courseId << endl;
        cout << "Course Name: " << courseName << endl;
        cout << "Credits: " << credits << endl;
        cout << "Instructor: " << instructor << endl;
        cout << "Schedule: " << schedule << endl;
    }
};

int main() {
    Student s1("Murtaza", "0782", "Pakistan Chowk", "03327327086", "k240782@nu.edu.pk", "Computer Science", 3.8, 2024);
    Professor p1("Sir Shafique", "P001", "Highway", "033111111111", "shafique.rehman@nu.edu.pk", "Computer Scienc", "OOP Lab", 90000);
    Staff staff1("Ahmed", "ST001", "FAST", "033222222222", "ahmed@email.com", "Administration", "Registrar", 50000);
    Course c1("CS1005", "Object Oriented Programming", 3, "Sir Shafique", "Monday and Tuesday 8 AM");
    s1.displayInfo();
    cout << endl;
    p1.displayInfo();
    cout << endl;
    staff1.displayInfo();
    cout << endl;
    c1.displayCourseInfo();
    cout << endl;
    c1.registerStudent(s1);
    cout << endl;
    c1.calculateGrades();
    return 0;
}
