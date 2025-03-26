#include <iostream>
#include <string>
using namespace std;

class Device {
protected:
    string deviceID;
    string deviceType;
    double powerRating;
    bool status;

public:
    Device(string id, string type, double pR, bool s = false) 
        : deviceID(id), deviceType(type), powerRating(pR), status(s) {}

    virtual void turnOn() {
        status = true;
        cout << deviceType << " [ID: " << deviceID << "] turned ON" << endl;
    }

    virtual void turnOff() {
        status = false;
        cout << deviceType << " [ID: " << deviceID << "] turned OFF" << endl;
    }

    virtual double calculatePowerUsage(int hours) = 0;

    string getDeviceID() const { return deviceID; }
    string getDeviceType() const { return deviceType; }
    bool getStatus() const { return status; }
};

class Light : public Device {
public:
    Light(string id, string type, double pR, bool s = false) 
        : Device(id, type, pR, s) {}

    double calculatePowerUsage(int hours) override {
        return status ? powerRating * hours : 0;
    }
};

class Fan : public Device {
    int speedLevel; 

public:
    Fan(string id, string type, double pR, bool s = false, int speed = 1) 
        : Device(id, type, pR, s), speedLevel(speed) {}

    void turnOn() override {
        Device::turnOn();
        cout << "Operating at speed level: " << speedLevel << endl;
    }

    void setSpeed(int speed) {
        if (speed >= 1 && speed <= 3) {
            speedLevel = speed;
            if (status) {
                cout << "Fan speed adjusted to level " << speedLevel << endl; } }
    }

    double calculatePowerUsage(int hours) override {
        if (!status) return 0;
        double speedFactor = 0.5 + (speedLevel * 0.5); 
        return powerRating * hours * speedFactor;
    }
};

class AC : public Device {
    double currentTemp;
    double desiredTemp;

public:
    AC(string id, string type, double pR, bool s = false, double cT = 30.0, double dT = 25.0) 
        : Device(id, type, pR, s), currentTemp(cT), desiredTemp(dT) {}

    void turnOn() override {
        if (currentTemp > desiredTemp) {
            Device::turnOn();
            cout << "Cooling to " << desiredTemp << "C" << endl; } 
		else {
            cout << "Temperature already at desired level" << endl; }
    }

    void setTemperature(double temp) {
        desiredTemp = temp;
        if (status) {
            cout << "New temperature set to " << desiredTemp << "C" << endl; }
    }

    double calculatePowerUsage(int hours) override {
        if (!status) return 0;
        double tempDifference = currentTemp - desiredTemp;
        double efficiencyFactor = 0.7 + (tempDifference * 0.01);
        return powerRating * hours * efficiencyFactor;
    }
};

class SecuritySystem : public Device {
    string securityStatus;
    const string password;

    bool authenticate() {
        string input;
        cout << "Enter security password: ";
        cin >> input;
        return input == password;
    }

public:
    SecuritySystem(string id, string type, double pR, string pwd, bool s = false) 
        : Device(id, type, pR, s), password(pwd), securityStatus("Standby") {}

    void turnOn() override {
        if (authenticate()) {
            Device::turnOn();
            securityStatus = "Armed";
            cout << "Security system ARMED" << endl; } 
		else {
            cout << "Access denied. Security remains OFF" << endl; }
    }

    void turnOff() override {
        if (authenticate()) {
            Device::turnOff();
            securityStatus = "Standby";
            cout << "Security system DISARMED" << endl; } 
		else {
            cout << "Access denied. Security remains ON" << endl; }
    }

    double calculatePowerUsage(int hours) override {
        return status ? powerRating * hours : powerRating * 0.1 * hours; 
    }

    friend class MaintenanceTool;
};

class User {
protected:
    string userID;
    string userRole;
    int accessLevel;

public:
    User(string id, string role, int level) 
        : userID(id), userRole(role), accessLevel(level) {}

    virtual void viewDevices() {
        cout << userRole << " can view basic devices (Lights, Fans, ACs)" << endl;
    }

    string getID() const { return userID; }
    string getRole() const { return userRole; }
    int getAccessLevel() const { return accessLevel; }
};

class AdminUser : public User {
public:
    AdminUser(string id, string role, int level) : User(id, role, level) {}

    void viewDevices() override {
        cout << userRole << " can view ALL devices including security systems" << endl;
    }

    void checkSecurityLogs(SecuritySystem& system) {
        if (accessLevel >= 2) {
            cout << "Accessing security logs..." << endl;
            cout << "Current status: " << (system.getStatus() ? "Armed" : "Disarmed") << endl; } 
		else {
            cout << "Unable to view security logs" << endl; }
    }
};

class MaintenanceTool {
public:
    static void diagnosticCheck(SecuritySystem& system) {
        cout << "Running diagnostic check..." << endl;
        cout << "System ID: " << system.getDeviceID() << endl;
        cout << "Power Status: " << (system.getStatus() ? "ON" : "OFF") << endl;
        cout << "Security Status: " << system.securityStatus << endl;
    }

    static void resetSystem(SecuritySystem& system) {
        system.status = false;
        system.securityStatus = "Standby";
        cout << "Security system has been reset" << endl;
    }
};

int main() {
    Light livingRoomLight("LR001", "Smart Bulb", 10);
    Fan bedroomFan("BR001", "Ceiling Fan", 50, false, 2);
    AC livingRoomAC("LRAC01", "Split AC", 1500);
    SecuritySystem homeSecurity("HS001", "Alarm System", 100, "admin123");
    User regularUser("U1001", "Regular User", 1);
    AdminUser adminUser("A1001", "System Admin", 2);
    livingRoomLight.turnOn();
    bedroomFan.turnOn();
    livingRoomAC.turnOn();
    homeSecurity.turnOn();
    cout << "\nPower Usage Report:" << endl;
    cout << "Light: " << livingRoomLight.calculatePowerUsage(5) << " Wh" << endl;
    cout << "Fan: " << bedroomFan.calculatePowerUsage(3) << " Wh" << endl;
    cout << "AC: " << livingRoomAC.calculatePowerUsage(2) << " Wh" << endl;
    cout << "Security: " << homeSecurity.calculatePowerUsage(24) << " Wh" << endl;
    cout << "\nUser Access:" << endl;
    regularUser.viewDevices();
    adminUser.viewDevices();
    adminUser.checkSecurityLogs(homeSecurity);
    cout << "\nMaintenance Operations:" << endl;
    MaintenanceTool::diagnosticCheck(homeSecurity);
    MaintenanceTool::resetSystem(homeSecurity);
    return 0;
}
