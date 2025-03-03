#include <iostream>
using namespace std;

class Square {
private:
    float sideLength;
    float area;
    static float allareas;  

public:
    Square() {
        sideLength = 0;
        area = 0;
    }

    Square(float sideLength) {
        this->sideLength = sideLength;
        area = 0;
    }

    void calculateArea() {
        area = sideLength * sideLength;
        allareas += area;  
    }

    float getSideLength() const {
        return sideLength;
    }

    float getArea() const {
        return area;
    }

    static float getAllAreas() {
        return allareas;
    }

    void setSideLength(float length) {
        sideLength = length;
    }

    void setArea(float a) {
        area = a;
    }
};

float Square::allareas = 0;

int main() {
    Square square1(4.0), square2(5.0), square3(6.0);
    square1.calculateArea();
    cout << "Square 1: Area = " << square1.getArea() << ", All Areas = " << Square::getAllAreas() << endl;
    square2.calculateArea();
    cout << "Square 2: Area = " << square2.getArea() << ", All Areas = " << Square::getAllAreas() << endl;
    square3.calculateArea();
    cout << "Square 3: Area = " << square3.getArea() << ", All Areas = " << Square::getAllAreas() << endl;
    return 0;
}
