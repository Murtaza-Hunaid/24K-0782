#include <iostream>
#include <cmath>
using namespace std;

class Shape {
protected:
    float x, y; 
    string color;
    float borderThickness;

public:
    Shape(float xPos, float yPos, string c, float bThickness = 1.0f) : x(xPos), y(yPos), color(c), borderThickness(bThickness) {}

    virtual void draw() {
        cout << "Drawing Shape at position (" << x << ", " << y << ") with color " << color << " and border thickness " << borderThickness << endl;
    }

    virtual float calculateArea() {
        return 0.0f;
    }

    virtual float calculatePerimeter() {
        return 0.0f;
    }
};

class Circle : public Shape {
private:
    float radius;

public:
    Circle(float xPos, float yPos, string c, float r, float bThickness = 1.0f) : Shape(xPos, yPos, c, bThickness), radius(r) {}

    void draw() override {
        cout << "Drawing Circle at center (" << x << ", " << y << ") with radius " << radius << ", color " << color << ", and border thickness " << borderThickness << endl;
    }

    float calculateArea() override {
        return 3.14159f * radius * radius;
    }

    float calculatePerimeter() override {
        return 2 * 3.14159f * radius;
    }
};

class Rectangle : public Shape {
private:
    float width, height;

public:
    Rectangle(float xPos, float yPos, string c, float w, float h, float bThickness = 1.0f) : Shape(xPos, yPos, c, bThickness), width(w), height(h) {}

    void draw() override {
        cout << "Drawing Rectangle at top-left corner (" << x << ", " << y << ") with width " << width << ", height " << height << ", color " << color << ", and border thickness " << borderThickness << endl;
    }

    float calculateArea() override {
        return width * height;
    }

    float calculatePerimeter() override {
        return 2 * (width + height);
    }
};

class Triangle : public Shape {
private:
    float sideA, sideB, sideC;

public:
    Triangle(float xPos, float yPos, string c, float a, float b, float cSide, float bThickness = 1.0f) : Shape(xPos, yPos, c, bThickness), sideA(a), sideB(b), sideC(cSide) {}

    void draw() override {
        cout << "Drawing Triangle at position (" << x << ", " << y << ") with sides " << sideA << ", " << sideB << ", " << sideC << ", color " << color << ", and border thickness " << borderThickness << endl;
    }

    float calculateArea() override {
        float s = (sideA + sideB + sideC) / 2;
        return sqrt(s * (s - sideA) * (s - sideB) * (s - sideC));
    }

    float calculatePerimeter() override {
        return sideA + sideB + sideC;
    }
};

class Polygon : public Shape {
private:
    int numberOfSides;
    float sideLength;

public:
    Polygon(float xPos, float yPos, string c, int nSides, float sLength, float bThickness = 1.0f) : Shape(xPos, yPos, c, bThickness), numberOfSides(nSides), sideLength(sLength) {}

    void draw() override {
        cout << "Drawing Polygon at position (" << x << ", " << y << ") with " << numberOfSides << " sides, each of length " << sideLength << ", color " << color << ", and border thickness " << borderThickness << endl;
    }

    float calculateArea() override {
        if (numberOfSides < 3)
            return 0.0f; 
        float perimeter = calculatePerimeter();
        float apothem = sideLength / (2 * tan(3.14159f / numberOfSides));
        return (perimeter * apothem) / 2;
    }

    float calculatePerimeter() override {
        return numberOfSides * sideLength;
    }
};

int main() {
    Circle circle(0.0f, 0.0f, "Red", 5.0f);
    Rectangle rectangle(1.0f, 1.0f, "Blue", 4.0f, 6.0f);
    Triangle triangle(2.0f, 2.0f, "Green", 3.0f, 4.0f, 5.0f);
    Polygon polygon(3.0f, 3.0f, "Yellow", 5, 2.0f);
    circle.draw();
    cout << "Area: " << circle.calculateArea() << endl;
    cout << "Perimeter: " << circle.calculatePerimeter() << endl << endl;
    rectangle.draw();
    cout << "Area: " << rectangle.calculateArea() << endl;
    cout << "Perimeter: " << rectangle.calculatePerimeter() << endl << endl;
    triangle.draw();
    cout << "Area: " << triangle.calculateArea() << endl;
    cout << "Perimeter: " << triangle.calculatePerimeter() << endl << endl;
    polygon.draw();
    cout << "Area: " << polygon.calculateArea() << endl;
    cout << "Perimeter: " << polygon.calculatePerimeter() << endl;
    return 0;
}
