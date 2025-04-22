#include <iostream>
#include <fstream>
using namespace std;

int main() {
    ofstream outFile("info.txt", ios::out);
    outFile << "C++ is a powerful programming language.";
    outFile.close();

    fstream file("info.txt", ios::in | ios::out);

    cout << "Initial get pointer position: " << file.tellg() << endl;
    cout << "Initial put pointer position: " << file.tellp() << endl;

    file.seekg(9); //using 9 instead of 6 as 6 reads ' a power' instead of 'powerful' as given in question.
    char word[9];
    file.read(word, 8);
    word[8] = '\0';
    cout << "Word read from position 6: " << word << endl;

    file.seekp(9);
    file.write("dynamic", 8);

    cout << "New get pointer position: " << file.tellg() << endl;
    cout << "New put pointer position: " << file.tellp() << endl;

    file.seekg(0);
    string line;
    getline(file, line);
    cout << "Updated file content: " << line << endl;

    file.close();

    return 0;
}
