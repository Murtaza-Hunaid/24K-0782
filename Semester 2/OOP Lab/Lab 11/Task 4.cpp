#include <iostream>
#include <cmath>
#include <type_traits>
#include <string>
using namespace std;

class NegativeNumberException : public exception {
public:
    const char* what() const noexcept override {
        return "NegativeNumberException - Input must be non-negative!";
    }
};

class InvalidTypeException : public exception {
public:
    const char* what() const noexcept override {
        return "InvalidTypeException - Non-numeric type detected!";
    }
};

template <typename T>
typename enable_if<is_arithmetic<T>::value, double>::type
sqrt_custom(T num) {
    if (num < 0) {
        throw NegativeNumberException(); }
    return sqrt(static_cast<double>(num));
}

template <typename T>
typename enable_if<!is_arithmetic<T>::value, double>::type
sqrt_custom(T) {
    throw InvalidTypeException();
}

int main() {
    try {
        cout << "sqrt(-4): " << sqrt_custom(-4) << endl; } 
	catch (const exception& e) {
        cout << "sqrt(-4): " << e.what() << endl; }

    try {
        cout << "sqrt(hello): " << sqrt_custom(string("hello")) << endl; } 
	catch (const exception& e) {
        cout << "sqrt(hello): " << e.what() << endl; }
    return 0;
}
