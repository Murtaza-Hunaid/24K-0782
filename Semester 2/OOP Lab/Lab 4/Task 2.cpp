#include <iostream>
#include <string>
using namespace std;

class Book {
    string id, title, author;
    bool availability;

public:
    Book(string id = "", string title = "", string author = "", bool availability = true) {
        this->id = id;
        this->title = title;
        this->author = author;
        this->availability = availability;
    }

    void setID(string id) { 
		this->id = id; }
    void setTitle(string title) { 
		this->title = title; }
    void setAuthor(string author) { 
		this->author = author; }
    void setAvailability(bool availability) { 
		this->availability = availability; }

    string getID() { 
		return id; }
    string getTitle() { 
		return title; }
    string getAuthor() { 
		return author; }
    bool getAvailability() { 
		return availability; }
};

class Library {
    Book* books; 
    int num_books; 

public:
    Library() {
        books = NULL;
        num_books = 0;
    }

    Library(int num_books) {
        this->num_books = num_books;
        books = new Book[num_books];
    }

    void addBook() {
        string id, title, author;
        cout << "Enter the ID of the book: ";
        cin.ignore();
        getline(cin, id);
        cout << "Enter the title of the book: ";
        getline(cin, title);
        cout << "Enter the author of the book: ";
        getline(cin, author);
        Book* newBooks = new Book[num_books + 1];
        for (int i = 0; i < num_books; i++) {
            newBooks[i] = books[i]; }
        newBooks[num_books] = Book(id, title, author);
        delete[] books;
        books = newBooks;
        num_books++;
        cout << "Book added successfully.\n"; }

    void borrowBook() {
        if (num_books <= 0) {
            cout << "No books available in the library.\n";
            return; }
        string bookTitle;
        cin.ignore();
        cout << "Enter the title of the book to borrow: ";
        getline(cin, bookTitle);
        for (int i = 0; i < num_books; i++) {
            if (books[i].getTitle() == bookTitle) {
                if (books[i].getAvailability()) {
                    books[i].setAvailability(false);
                    cout << "You have borrowed the book: " << books[i].getTitle() << endl; } 
				else {
                    cout << "The book is already borrowed\n"; }
                return; } }
        cout << "Book not found in the library\n";
    }

    void returnBook() {
        if (num_books <= 0) {
            cout << "No books available in the library\n";
            return; }
        string bookTitle;
        cin.ignore();
        cout << "Enter the title of the book to return: ";
        getline(cin, bookTitle);
        for (int i = 0; i < num_books; i++) {
            if (books[i].getTitle() == bookTitle) {
                if (!books[i].getAvailability()) {
                    books[i].setAvailability(true);
                    cout << "You have returned the book: " << books[i].getTitle() << endl; } 
				else {
                    cout << "The book is already available in the library\n"; }
                return; } }
        cout << "Book not found in the library\n";
    }

    void displayBooks() {
        if (num_books <= 0) {
            cout << "No books available in the library\n";
            return; }
        cout << "\n----- List of Books -----\n";
        for (int i = 0; i < num_books; i++) {
            cout << "ID: " << books[i].getID() << endl;
			cout << "Title: " << books[i].getTitle() << endl;
			cout << "Author: " << books[i].getAuthor() << endl;
			cout << "Availability: ";
			if (books[i].getAvailability()) {
    			cout << "Available" << endl; } 
			else {
    			cout << "Borrowed" << endl; }
			cout << endl; } 
	}
    ~Library() {
        delete[] books;
    }
};

int main() {
    Library lib;
    int choice;
    while (true) {
        cout << "\n----- Library System -----\n";
        cout << "1. Add Book\n";
        cout << "2. Display Books\n";
        cout << "3. Borrow Book\n";
        cout << "4. Return Book\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        if (choice == 1) {
            lib.addBook(); } 
		else if (choice == 2) {
            lib.displayBooks(); } 
		else if (choice == 3) {
            lib.borrowBook(); } 
		else if (choice == 4) {
            lib.returnBook(); } 
		else if (choice == 5) {
            cout << "Exiting the Library System\n";
            break; } 
		else {
            cout << "Invalid choice. Please try again.\n"; } }
    return 0;
}
