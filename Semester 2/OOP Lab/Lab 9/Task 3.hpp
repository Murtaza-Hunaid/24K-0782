#ifndef TASK3_H
#define TASK3_H

#include <iostream>
#include <string>
using namespace std;

class Book {
private:
    string title;
    string author;
    string ISBN;

public:
    Book(string t, string a, string isbn);  
    string getTitle() const;              
    string getAuthor() const;             
    string getISBN() const;                
};

#endif
