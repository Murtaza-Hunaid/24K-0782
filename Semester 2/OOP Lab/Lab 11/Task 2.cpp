#include <iostream>
#include <exception>
using namespace std;

class StackOverflowException : public exception {
public:
    const char* what() const noexcept override {
        return "StackOverflowException - Stack is full!";
    }
};

class StackUnderflowException : public exception {
public:
    const char* what() const noexcept override {
        return "StackUnderflowException - Stack is empty!";
    }
};

template <typename T>
class Stack {
private:
    T* arr;
    int top;
    int capacity;

public:
    Stack(int size) {
        capacity = size;
        arr = new T[capacity];
        top = -1;
    }

    ~Stack() {
        delete[] arr;
    }

    void push(T value) {
        if (top == capacity - 1) {
            throw StackOverflowException(); }
        arr[++top] = value;
    }

    T pop() {
        if (top == -1) {
            throw StackUnderflowException(); }
        return arr[top--];
    }
};

int main() {
    Stack<int> s(2);
    try {
        s.push(10);
        s.push(20);
        s.push(30); } 
	catch (const exception& e) {
        cout << "Pushing to a full stack: " << e.what() << endl; }

    try {
        s.pop();
        s.pop();
        s.pop(); } 
	catch (const exception& e) {
        cout << "Popping from an empty stack: " << e.what() << endl; }
    return 0;
}
