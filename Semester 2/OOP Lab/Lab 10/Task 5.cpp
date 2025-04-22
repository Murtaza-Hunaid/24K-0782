#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main() {
    fstream file("data.txt", ios::in | ios::out);
    if (!file) {
        ofstream create("data.txt");
        create << "AI is the future. AI will transform the world. Embrace AI now.";
        create.close();
        file.open("data.txt", ios::in | ios::out); }

    string searchWord, replacementWord;
    cout << "Enter word to search: ";
    cin >> searchWord;
    cout << "Enter replacement word: ";
    cin >> replacementWord;
    if (replacementWord.length() > searchWord.length()) {
        cout << "Replacement word must not be longer than the search word." << endl;
        return 0; }

    file.clear();
    file.seekg(0, ios::beg);
    string buffer;
    char ch;
    streampos start;
    while (file.get(ch)) {
        if (isalpha(ch)) {
            start = file.tellg();
            buffer = ch;
            while (file.get(ch) && isalpha(ch)) {
                buffer += ch; }
            file.unget();
            if (buffer == searchWord) {
                streampos writePos = start - static_cast<streamoff>(buffer.length());
                file.seekp(writePos);
                file.write(replacementWord.c_str(), replacementWord.length());
                for (size_t i = replacementWord.length(); i < buffer.length(); ++i) {
                    file.put(' '); }
                file.seekg(start); } } }
    file.close();
    ifstream inFile("data.txt");
    string line;
    while (getline(inFile, line)) {
        cout << line << endl; }
    inFile.close();

    return 0;
}
