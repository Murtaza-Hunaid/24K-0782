#include <iostream>
using namespace std;

class ValidateString {
private:
    string str;

public:
    ValidateString(string input) {
        str = input;
    }

    // Constant function because we are not modifying the object inside this function. A constant member function does not modify the state of the object.
    void isValid() const {
        bool valid = true;
        for (int i = 0; i < str.size(); i++) {
            char c = str[i];
            if (c >= 'a' && c <= 'z')
                continue;
            if (c >= 'A' && c <= 'Z')
                continue;
            valid = false;
            break; }
        cout << "String " << str << " is " << (valid ? "valid" : "invalid") << endl;
    }
};


int main() {
    ValidateString str1("Hello"), str2("Murtaza0782"), str3("murtaza@gmail.com"); 
    str1.isValid();
    str2.isValid();
    str3.isValid();
    return 0;
}
