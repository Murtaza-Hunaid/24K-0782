#include <iostream>
#include <string>
using namespace std;

class Calendar {
private:
    string tasks[12][31]; 
    int current_year;      

public:
    Calendar(int year) : current_year(year) {
        for (int i = 0; i < 12; i++) {
            for (int j = 0; j < 31; j++) {
                tasks[i][j] = ""; } }
    }

    void addTask(const string& task, int day, int month) {
        if (month < 1 || month > 12 || day < 1 || day > 31) {
            cout << "Invalid date.\n";
            return; }
        tasks[month - 1][day - 1] = task;
        cout << "Task added: " << task << " on " << day << "/" << month << ".\n";
    }

    void removeTask(int day, int month) {
        if (month < 1 || month > 12 || day < 1 || day > 31) {
            cout << "Invalid date.\n";
            return; }
        if (tasks[month - 1][day - 1].empty()) {
            cout << "No task to remove on " << day << "/" << month << ".\n"; } 
		else {
            cout << "Task removed: " << tasks[month - 1][day - 1] << " from " << day << "/" << month << ".\n";
            tasks[month - 1][day - 1] = ""; }
    }

    void showTasks() const {
        cout << "Tasks for year " << current_year << ":\n";
        for (int i = 0; i < 12; i++) {
            for (int j = 0; j < 31; j++) {
                if (!tasks[i][j].empty()) {
                    cout << "Month " << (i + 1) << ", Day " << (j + 1) << ": " << tasks[i][j] << endl; } } }
	}
};

int main() {
    Calendar calendar(2025);
    calendar.addTask("Doctor's appointment", 5, 2);
    calendar.addTask("Project deadline", 10, 3);
    calendar.addTask("Clothes Shopping", 15, 4);
    calendar.addTask("Vacation starts", 20, 6);
    calendar.addTask("Breakfast with friends", 25, 7);
    calendar.addTask("University Event", 30, 8);
    calendar.showTasks();
    calendar.removeTask(10, 3);
	calendar.removeTask(15, 4);
	calendar.removeTask(25, 7);
    calendar.showTasks();
    return 0;
}
