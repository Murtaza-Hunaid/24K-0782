#include <iostream>
#include <fstream>
using namespace std;

int main() {
    string name, email, summary;
    int yearsOfExperience;
    cout << "Enter your name: ";
    getline(cin, name);
    cout << "Enter your email: ";
    getline(cin, email);
    cout << "Enter your years of experience: ";
    cin >> yearsOfExperience;
    cin.ignore();
    cout << "Enter a brief summary of your experience: ";
    getline(cin, summary);
    
    ofstream outFile("resume.txt", ios::trunc);
    outFile << "Name: " << name << endl;
    outFile << "Email: " << email << endl;
    outFile << "Years of Experience: " << yearsOfExperience << endl;
    outFile << "Summary: " << summary << endl;
    outFile.close();
    
    ifstream inFile("resume.txt");
    string line;
    cout << "\nResume content after update:\n";
    while (getline(inFile, line)) {
        cout << line << endl; }
    inFile.close();
    
    return 0;
}
