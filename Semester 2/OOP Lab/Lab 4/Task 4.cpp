#include <iostream>
#include <string>
using namespace std;

class Car {
private:
    int carID;
    string model;
    int year;
    bool isRented;

public:
    Car() {
        isRented = false;
    }

    Car(int id, string mod, int yr) {
        carID = id;
        model = mod;
        year = yr;
        isRented = false;
    }

    void rentCar() {
        if (!isRented) {
            isRented = true;
            cout << "Car with ID " << carID << " has been rented.\n"; } 
        else {
            cout << "Car with ID " << carID << " is already rented.\n"; }
    }

    void returnCar() {
        if (isRented) {
            isRented = false;
            cout << "Car with ID " << carID << " has been returned.\n"; } 
        else {
            cout << "Car with ID " << carID << " is already available.\n"; }
    }

    bool isVintage() const {
        if (year < 2000) {
            return true; }
        else {
            return false; } 
    }

};

int main() {
    Car car1(782, "Pagani Zonda", 1999);
    Car car2(687, "LaFerrari", 2013);
    Car car3(651, "Ferrari F40", 1987);
    car1.rentCar();
    car1.returnCar();
    car1.rentCar();
    car2.rentCar();
    car2.returnCar();
    if (car3.isVintage()) {
        cout << "The car is vintage" << endl; } 
    else {
        cout << "The car is not vintage" << endl; }
    return 0;
}
