#include "Task3.h"
#include <iostream>
#include <string>

Book::Book(string t, string a, string isbn) : title(t), author(a), ISBN(isbn) {}

string Book::getTitle() const {
    return title;
}

string Book::getAuthor() const {
    return author;
}

string Book::getISBN() const {
    return ISBN;
}

class Library {
private:
    Book* books[100]; 
    int bookCount;     

public:
    Library() : bookCount(0) {}

    void addBook(Book* book) {
        if (bookCount < 100) {
            books[bookCount++] = book; } 
        else {
            cout << "Library is full, cannot add more books" << endl; }
    }

    void removeBook(const string& isbn) {
        for (int i = 0; i < bookCount; ++i) {
            if (books[i]->getISBN() == isbn) {
                for (int j = i; j < bookCount - 1; ++j) {
                    books[j] = books[j + 1]; }
                --bookCount;
                break; } }
    }

    Book* searchBook(const string& isbn) {
        for (int i = 0; i < bookCount; ++i) {
            if (books[i]->getISBN() == isbn) {
                return books[i]; } }
        return nullptr;
    }

    void displayBooks() {
        if (bookCount == 0) {
            cout << "No books in the library." << endl;
            return; }
        for (int i = 0; i < bookCount; ++i) {
            cout << "Title: " << books[i]->getTitle() << ", Author: " << books[i]->getAuthor() << ", ISBN: " << books[i]->getISBN() << endl; }
    }
};

int main() {
    Book book1("Lord Of The Rings", "J.R.R. Tolkien", "9780544003415");
    Book book2("To Kill a Mockingbird", "Harper Lee", "9780061120084");

    Library library;
    library.addBook(&book1);
    library.addBook(&book2);

    cout << "Library Books:" << endl;
    library.displayBooks();

    string searchISBN = "9780544003415";
    Book* foundBook = library.searchBook(searchISBN);
    if (foundBook) {
        cout << "\nFound Book - Title: " << foundBook->getTitle() << ", Author: " << foundBook->getAuthor() << ", ISBN: " << foundBook->getISBN() << endl; } 
    else {
        cout << "Book with ISBN " << searchISBN << " not found." << endl; }

    library.removeBook("9780061120084");

    cout << "\nLibrary Books After Removal:" << endl;
    library.displayBooks();

    return 0;
}
