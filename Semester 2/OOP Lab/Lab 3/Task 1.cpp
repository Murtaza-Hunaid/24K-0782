#include <iostream>
using namespace std;

class Time{
    int hours, minutes, seconds;

public:
    Time(){
        hours = 0;
        minutes = 0;
        seconds = 0;
    }

    Time(int hrs, int mins, int secs){
        hours = hrs;
        minutes = mins;
        seconds = secs;
    }

    void displayTime(){
        cout << hours << ":" << minutes << ":" << seconds << endl;
    }

    Time addTime(const Time &a, const Time &b){
        Time total;
        total.hours = a.hours + b.hours;
        total.minutes = a.minutes + b.minutes;
        total.seconds = a.seconds + b.seconds;

        if(total.minutes >= 60){
            total.hours++;
            total.minutes -= 60; }

        if(total.seconds >= 60){
            total.minutes++;
            total.seconds -= 60; }
        return total;
    }
};

int main(){
    int s1, s2, m1, m2, h1, h2;
    cout << "Enter the hours, minutes and seconds for time 1: ";
    cin >> h1 >> m1 >> s1;
    cout << "Enter the hours, minutes and seconds for time 2: ";
    cin >> h2 >> m2 >> s2;
    Time t1(h1, m1, s1), t2(h2, m2, s2), t3;
    cout << "Time 1: ";
    t1.displayTime();
    cout << "Time 2: ";
    t2.displayTime();
    t3 = t3.addTime(t1, t2);
    cout << "The new time after adding is ";
    t3.displayTime(); 
    return 0;
}
