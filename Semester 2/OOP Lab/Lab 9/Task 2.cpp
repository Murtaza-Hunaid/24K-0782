#include <iostream>
using namespace std;

class SmartDevice {
public:
    virtual void turnOn() = 0;
    virtual void turnOff() = 0;
    virtual void getStatus() = 0;
};

class LightBulb : public SmartDevice {
private:
    bool isOn;
    int brightness;

public:
    LightBulb(bool initialOn = false, int initialBrightness = 0) : isOn(initialOn), brightness(initialBrightness) {}

    void turnOn() override {
        isOn = true;
        brightness = 100;
    }

    void turnOff() override {
        isOn = false;
        brightness = 0;
    }

    void getStatus() override {
        cout << "LightBulb is " << (isOn ? "On" : "Off") << ", Brightness: " << brightness << "%" << endl;
    }
};

class Thermostat : public SmartDevice {
private:
    bool isOn;
    double temperature;

public:
    Thermostat(bool initialOn = false, double initialTemperature = 35) : isOn(initialOn), temperature(initialTemperature) {}

    void turnOn() override {
        isOn = true;
        temperature = 25.0;
    }

    void turnOff() override {
        isOn = false;
    }

    void getStatus() override {
        cout << "Thermostat is " << (isOn ? "On" : "Off") << ", Temperature: " << temperature << " C" << endl;
    }
};

int main() {
    LightBulb bulb(true, 50); 
    Thermostat thermostat(true, 35); 

    SmartDevice* devices[] = { &bulb, &thermostat };

    for (int i = 0; i < 2; i++) {
        devices[i]->getStatus(); }

    bulb.turnOn();
    thermostat.turnOn();

    for (int i = 0; i < 2; i++) {
        devices[i]->getStatus(); }

    bulb.turnOff();
    thermostat.turnOff();

    for (int i = 0; i < 2; i++) {
        devices[i]->getStatus(); }

    return 0;
}
