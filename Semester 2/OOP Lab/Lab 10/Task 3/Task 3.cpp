#include <iostream>
#include <fstream>
using namespace std;

int main() {
    ifstream chapter1("chapter1.txt");
    ifstream chapter2("chapter2.txt");
    ofstream book("book.txt", ios::app);

    string line;

    while (getline(chapter1, line)) {
        book << line << endl; }
    book << endl;

    while (getline(chapter2, line)) {
        book << line << endl; }

    chapter1.close();
    chapter2.close();
    book.close();
    ifstream displayBook("book.txt");
    cout << "\nContents of book.txt after merging chapters:\n";
    while (getline(displayBook, line)) {
        cout << line << endl; }

    displayBook.close();
    return 0;
}
