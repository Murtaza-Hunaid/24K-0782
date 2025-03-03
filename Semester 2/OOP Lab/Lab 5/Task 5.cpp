#include <iostream>
using namespace std;

class Engine {
private:
    string type;
public:
    Engine(string t = "Default") : type(t) { cout << "Engine created: " << type << "\n"; }
    void setType(string t) { type = t; }
    string getType() { return type; }
};

class Wheels {
private:
    int size;
public:
    Wheels(int s = 16) : size(s) { cout << "Wheels created: " << size << " inches\n"; }
    void setSize(int s) { size = s; }
    int getSize() { return size; }
};

class Headlights {
private:
    string brightness;
public:
    Headlights(string b = "Standard") : brightness(b) { cout << "Headlights created: " << brightness << "\n"; }
    void setBrightness(string b) { brightness = b; }
    string getBrightness() { return brightness; }
};

class Steering {
private:
    string type;
public:
    Steering(string t = "Power") : type(t) { cout << "Steering created: " << type << "\n"; }
    void setType(string t) { type = t; }
    string getType() { return type; }
};

class Car {
private:
    Engine engine;
    Wheels wheels;
    Headlights headlights;
    Steering *steering;

public:
    Car(Steering *s, string eType, int wSize, string hBrightness) : steering(s), engine(eType), wheels(wSize), headlights(hBrightness) { cout << "Car created\n"; }
    ~Car() { cout << "Car destroyed\n"; }
    void setSteering(Steering *s) { steering = s; }
    void setEngine(string t) { engine.setType(t); }
    void setWheels(int s) { wheels.setSize(s); }
    void setHeadlights(string b) { headlights.setBrightness(b); }
};

int main() {
    Steering s("Hydraulic");
    Car car(&s, "V8", 18, "LED");
    Steering newSteering("Electric");
    car.setSteering(&newSteering);
    car.setEngine("V6");
    car.setWheels(20);
    car.setHeadlights("Xenon");
    return 0;
}
