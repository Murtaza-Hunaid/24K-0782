/*No, a friend function cannot access private and protected members of a class without using an object. 
Friend functions require an instance of the class to access its private members.*/


#include <iostream>
using namespace std;

class Number {
    int value;
public:
    Number(int v) : value(v) {}

    friend void showPrivateValue(Number obj);

    void display() { cout << "Value: " << value << endl; }
};

void showPrivateValue(Number obj) {
    cout << "Private value: " << obj.value << endl;  
}

int main() {
    Number num(20);
    showPrivateValue(num); 
    return 0;
}
