#include <iostream>
using namespace std;

class Activity {
public:
    virtual double calculateCaloriesBurned(double weight) = 0;
    virtual ~Activity() {}
};

class Running : public Activity {
private:
    double distance; 
    double time;     

public:
    Running(double d, double t) : distance(d), time(t) {}

    double calculateCaloriesBurned(double weight) override {
        double MET;
        double speed = (distance / time) * 60; 
        if (speed >=8) {
            MET = 11.5; }
        else{
            MET = 9.8; }
        return (MET * weight * time) / 60.0;
    }
};

class Cycling : public Activity {
private:
    double speed; 
    double time;  

public:
    Cycling(double s, double t) : speed(s), time(t) {}

    double calculateCaloriesBurned(double weight) override {
        double MET;
        if (speed < 16) MET = 4.0;
        else if (speed < 20) MET = 6.8;
        else MET = 8.0;
        return MET * weight * time;
    }
};

int main() {
    double weight;
    cout << "Enter your weight (kg): ";
    cin >> weight;

    Running run(5.0, 30.0);     
    Cycling cycle(18.0, 1.0);  

    Activity* activities[] = { &run, &cycle };

    cout << "Running - Calories Burned: " << activities[0]->calculateCaloriesBurned(weight) << endl;
    cout << "Cycling - Calories Burned: " << activities[1]->calculateCaloriesBurned(weight) << endl;
    return 0;
}
