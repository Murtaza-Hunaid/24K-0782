#include <iostream>
using namespace std;

#define PI 3.141592653

class Shape {
protected:
    double positionX;
    double positionY;
    string color;
    double borderThickness;

public:
    Shape(double x, double y, string col, double border = 1.0) : positionX(x), positionY(y), color(col), borderThickness(border) {}

    virtual void draw() = 0;
    virtual double calculateArea() = 0;
    virtual double calculatePerimeter() = 0;
};

class Circle : public Shape {
private:
    double radius;

public:
    Circle(double x, double y, string col, double r, double border = 1.0) : Shape(x, y, col, border), radius(r) {}

    void draw() override {
        cout << "Drawing Circle at (" << positionX << ", " << positionY << ") with radius " << radius << " and color " << color << endl;
    }

    double calculateArea() override {
        return PI * radius * radius;
    }

    double calculatePerimeter() override {
        return 2 * PI * radius;
    }
};

class Rectangle : public Shape {
private:
    double width;
    double height;

public:
    Rectangle(double x, double y, string col, double w, double h, double border = 1.0) : Shape(x, y, col, border), width(w), height(h) {}

    void draw() override {
        cout << "Drawing Rectangle at (" << positionX << ", " << positionY << ") with width " << width << " and height " << height << " and color " << color << endl;
    }

    double calculateArea() override {
        return width * height;
    }

    double calculatePerimeter() override {
        return 2 * (width + height);
    }
};

class Triangle : public Shape {
private:
    double side1;
    double side2;
    double side3;

public:
    Triangle(double x, double y, string col, double s1, double s2, double s3, double border = 1.0) : Shape(x, y, col, border), side1(s1), side2(s2), side3(s3) {}

    void draw() override {
        cout << "Drawing Triangle at (" << positionX << ", " << positionY << ") with sides " << side1 << ", " << side2 << ", " << side3 << " and color " << color << endl;
    }

    double calculateArea() override {
        double s = (side1 + side2 + side3) / 2;
        return sqrt(s * (s - side1) * (s - side2) * (s - side3));
    }

    double calculatePerimeter() override {
        return side1 + side2 + side3;
    }
};

class Polygon : public Shape {
private:
    double* sides;
    int numSides;

public:
    Polygon(double x, double y, string col, int n, double* s, double border = 1.0) : Shape(x, y, col, border), numSides(n) {
        sides = new double[numSides];
        for (int i = 0; i < numSides; ++i) {
            sides[i] = s[i];
        }
    }

    ~Polygon() {
        delete[] sides;
    }

    void draw() override {
        cout << "Drawing Polygon at (" << positionX << ", " << positionY << ") with " << numSides << " sides and color " << color << endl;
    }

    double calculateArea() override {
        cout << "Area calculation for an arbitrary polygon is not implemented." << endl;
        return 0.0;
    }

    double calculatePerimeter() override {
        double perimeter = 0;
        for (int i = 0; i < numSides; ++i) {
            perimeter += sides[i];
        }
        return perimeter;
    }
};

int main() {
    Circle circle(0, 0, "Red", 5);
    Rectangle rectangle(1, 1, "Blue", 4, 6);
    Triangle triangle(2, 2, "Green", 3, 4, 5);
    double polygonSides[] = {3, 4, 5, 6};
    Polygon polygon(3, 3, "Yellow", 4, polygonSides);

    circle.draw();
    cout << "Area: " << circle.calculateArea() << ", Perimeter: " << circle.calculatePerimeter() << endl;

    rectangle.draw();
    cout << "Area: " << rectangle.calculateArea() << ", Perimeter: " << rectangle.calculatePerimeter() << endl;

    triangle.draw();
    cout << "Area: " << triangle.calculateArea() << ", Perimeter: " << triangle.calculatePerimeter() << endl;

    polygon.draw();
    cout << "Perimeter: " << polygon.calculatePerimeter() << endl;

    return 0;
}
