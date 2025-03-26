/*Yes, a friend function can handle this case. It is especially useful when the primitive type is on the right-hand side, for e.g., 
object + int. If the primitive is on the left, for e.g., int + object, the friend function must be defined to handle that order.*/

#include <iostream>
using namespace std;

class Number {
private:
    int value;
public:
    Number(int v) : value(v) {}
    void print() const { cout << "Value: " << value << endl; }

    friend Number operator+(const Number& lhs, int rhs);

    friend Number operator+(int lhs, const Number& rhs);
};

Number operator+(const Number& lhs, int rhs) {
    return Number(lhs.value + rhs);
}

Number operator+(int lhs, const Number& rhs) {
    return Number(lhs + rhs.value);
}

int main() {
    Number obj(5);
    Number result1 = obj + 10; 
    result1.print(); 
    Number result2 = 10 + obj; 
    result2.print(); 
    return 0;
}
