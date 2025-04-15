#include <iostream>
#include <string>
using namespace std;

class Vehicle {
public:
    string model;
    double rate;

    Vehicle(string m, double r) : model(m), rate(r) {}

    virtual double getDailyRate() = 0;
    virtual void displayDetails() = 0;
};

class Car : public Vehicle {
public:
    Car(string m, double r) : Vehicle(m, r) {}

    double getDailyRate() override {
        return rate;
    }

    void displayDetails() override {
        cout << "Car Model: " << model << ", Daily Rate: " << rate << endl;
    }
};

class Bike : public Vehicle {
public:
    Bike(string m, double r) : Vehicle(m, r) {}

    double getDailyRate() override {
        return rate;
    }

    void displayDetails() override {
        cout << "Bike Model: " << model << ", Daily Rate: " << rate << endl;
    }
};

int main() {
    Car car("Honda City", 15000.0);
    Bike bike("Honda 125", 3000.0);

    Vehicle* vehicles[] = { &car, &bike };

    for (int i = 0; i < 2; i++) {
        vehicles[i]->displayDetails();
        cout << "Daily Rate: " << vehicles[i]->getDailyRate() << endl; }

    return 0;
}
