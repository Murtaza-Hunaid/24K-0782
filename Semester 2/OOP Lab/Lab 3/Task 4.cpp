#include <iostream>
#include <iomanip>

using namespace std;

class Angle {
private:
    int degrees;    
    float minutes;   
    char direction; 

public:
    Angle(int deg, float min, char dir) : degrees(deg), minutes(min), direction(dir) {}
    void inputAngle() {
        cout << "Enter degrees: ";
        cin >> degrees;
        cout << "Enter minutes: ";
        cin >> minutes;
        cout << "Enter direction (N, S, E, W): ";
        cin >> direction; }
    void displayAngle() const {
        cout << fixed << setprecision(1) << degrees << "\xF8" << minutes << "' " << direction << endl;
    }
};

int main() {
    Angle angle(150, 36.4, 'W');
    cout << "Initialized angle: ";
    angle.displayAngle();
    char choice;
    do {
        cout << "\nInput a new angle:\n";
        angle.inputAngle();
        cout << "You entered: ";
        angle.displayAngle();
        cout << "\nDo you want to input another angle? (y/n): ";
        cin >> choice; } 
	while (choice == 'y' || choice == 'Y');
    return 0;
}
