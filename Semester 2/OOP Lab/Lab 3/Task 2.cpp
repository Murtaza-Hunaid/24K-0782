#include <iostream>
#include <conio.h>
using namespace std;

class tollBooth
{
    unsigned int total_cars;
    double total_amount;

public:
    tollBooth()
    {
        total_cars = 0;
        total_amount = 0;
    }

    void payingCar()
    {
        total_cars++;
        total_amount += 0.50;
    }

    void nopayCar()
    {
        total_cars++;
    }

    void display()
    {
        cout << endl;
        cout << "The total number of cars that have gone by are " << total_cars << endl;
        cout << "The total amount of money collected is " << total_amount << " cents" << endl;
    }
};

int main()
{
    tollBooth t1;
    char choice;
    cout << "----- Toll Booth system -----" << endl;
    cout << "Press \'P\' for a paying car and \'N\' for a non-paying car" << endl;
    cout << "Press the Esc key to display the total cars passed and total cash collected" << endl;
    while (1)
    {
        cout << endl
             << "Enter your choice: ";
        choice = _getch();

        switch (choice)
        {
        case 'P':
        case 'p':
            t1.payingCar();
            cout << "Paying Car Passed" << endl;
            break;

        case 'N':
        case 'n':
            t1.nopayCar();
            cout << "Non-Paying Car Passed" << endl;
            break;

        case char(27):
            cout << "End" << endl;
            t1.display();
            cout << "Exiting the program" << endl;
            return 0;
        }
    }
}
