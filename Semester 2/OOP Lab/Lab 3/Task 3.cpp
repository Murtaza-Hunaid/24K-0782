#include <iostream>
using namespace std;

class Serial
{
    static int counter;
    int serial_number;

public:
    Serial()
    {
        serial_number = (++counter);
    }

    void displaySerialnumber()
    {
        cout << "I am object number " << serial_number << "." << endl;
    }

    static void showCounter()
    {
        cout << "The total number of objects created are " << counter << "." << endl;
    }
};

int Serial :: counter = 0;

int main()
{
    Serial obj1, obj2, obj3;
    obj1.displaySerialnumber();
    obj2.displaySerialnumber();
    obj3.displaySerialnumber();
    Serial :: showCounter();
    return 0;
}
