#include <iostream>
#include <string>
using namespace std;

class Employee {
private:
    int employeeID;
    string name;
    string department;
    double salary;

public:
    Employee() {
        salary = 0.0;
    }

    Employee(int id, string emp_name, string dept, double sal) {
        employeeID = id;
        name = emp_name;
        department = dept;
        salary = sal;
    }

    void giveBonus(double amount) {
        salary += amount;
    }

    bool isManager() {
        if (department == "Management") {
        	return true; }
        else {
        	return false; }
    }

    void displayDetails() {
        cout << "Employee ID: " << employeeID << endl;
        cout << "Name: " << name << endl;
        cout << "Department: " << department << endl;
        cout << "Salary: Rs." << salary << endl;
    }
};

int main() {
    Employee emp1(7820, "Murtaza", "Management", 75000.0); 
    Employee emp2(6875, "Adnan", "Engineering", 65000.0);
    cout << "Details of Employee 1:" << endl;
    emp1.displayDetails();
    cout << endl;
    cout << "Giving a bonus of $5000 to Employee 1" << endl;
    emp1.giveBonus(5000.0);
    emp1.displayDetails();
    cout << endl;
    if (emp1.isManager()) {
    	cout << "Is Employee 1 a Manager? Yes" << endl; } 
	else {
    	cout << "Is Employee 1 a Manager? No" << endl; }
	cout << endl;
    cout << "Details of Employee 2:" << endl;
    emp2.displayDetails();
    cout << endl;
    cout << "Giving a bonus of $3000 to Employee 2" << endl;
    emp2.giveBonus(3000.0);
    emp2.displayDetails();
    cout << endl;
    if (emp2.isManager()) {
    	cout << "Is Employee 2 a Manager? Yes" << endl; } 
	else {
    	cout << "Is Employee 2 a Manager? No" << endl; }
	cout << endl;
    return 0;
}
