#include <iostream>
#include <exception>
#include <string>
using namespace std;

class FileException : public exception {
public:
    virtual const char* what() const noexcept {
        return "FileException";
    }
};

class FileNotFoundException : public FileException {
public:
    const char* what() const noexcept override {
        return "FileNotFoundException - File not found!";
    }
};

class PermissionDeniedException : public FileException {
public:
    const char* what() const noexcept override {
        return "PermissionDeniedException - Access denied!";
    }
};

void readFile(const string& filename) {
    if (filename == "missing.txt") {
        throw FileNotFoundException(); } 
	else if (filename == "secret.txt") {
        throw PermissionDeniedException(); } 
	else {
        cout << "Reading '" << filename << "' successful." << endl; }
}

int main() {
    string filename = "secret.txt";
    try {
        readFile(filename); } 
	catch (const FileNotFoundException& e) {
        cout << "Reading '" << filename << "': " << e.what() << endl; } 
	catch (const PermissionDeniedException& e) {
        cout << "Reading '" << filename << "': " << e.what() << endl; } 
	catch (const FileException& e) {
        cout << "Reading '" << filename << "': " << e.what() << endl; }
    return 0;
}
