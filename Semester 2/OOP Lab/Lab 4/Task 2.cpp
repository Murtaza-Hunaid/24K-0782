#include <iostream>
using namespace std;

class Book
{
    string id;
    string title;
    string author;
    bool availability;

public:
    Book() {
        id = " ";
        title = " ";
        author = " ";
        availability = false;
    }

    Book(string id, string title, string author, bool availability) {
        this->id = id;
        this->title = title;
        this->author = author;
        this->availability = availability;
    }

    void setID(string id)
    {
        this->id = id;
    }

    void setTitle(string title)
    {
        this->title = title;
    }

    void setAuthor(string author)
    {
        this->author = author;
    }

    void setAvailability(bool availability)
    {
        this->availability = availability;
    }

    string getID()
    {
        return this->id;
    }

    string getTitle()
    {
        return this->title;
    }

    string getAuthor()
    {
        return this->author;
    }

    bool getAvailability()
    {
        return this->availability;
    }
};

class Library
{
    Book *books;
    int num;

public:
    Library()
    {
        books = nullptr;
        num = 0;
    }

    Library(int num)
    {
        this->num = num;
        books = new Book[this->num];
    }

    void addBook()
    {
        string id, title, author;
        bool availability;

        if (books == nullptr || num == 0)
        {
            books = new Book[1];
            cout << "Enter the ID of book 1: ";
            cin.ignore();
            getline(cin, id);
            cout << "Enter the title of book 1: ";
            getline(cin, title);
            cout << "Enter the author of book 1: ";
            getline(cin, author);
            books[0].setID(id);
            books[0].setTitle(title);
            books[0].setAuthor(author);
            books[0].setAvailability(true);
            num++;
        }
        else
        {
            Book *newBooks = new Book[num + 1];
            for (int i = 0; i < num; i++)
            {
                newBooks[i] = books[i];
            }

            cout << "Enter the ID of book " << (num + 1) << ": ";
            cin.ignore();
            getline(cin, id);
            cout << "Enter the title of book " << (num + 1) << ": ";
            getline(cin, title);
            cout << "Enter the author of book " << (num + 1) << ": ";
            getline(cin, author);

            newBooks[num].setID(id);
            newBooks[num].setTitle(title);
            newBooks[num].setAuthor(author);
            newBooks[num].setAvailability(true);

            delete[] books;
            books = newBooks;
            num++;
        }
    }

    void borrowBook()
    {
        if (books == nullptr || num <= 0)
        {
            cout << "No books have been initialized yet." << endl;
            return;
        }

        string bookTitle;
        cin.ignore();
        cout << "Enter the title of the book you would like to borrow: ";
        getline(cin, bookTitle);

        int i, flag = 0;
        for (i = 0; i < num; i++)
        {
            if (bookTitle == books[i].getTitle())
            {
                flag = 1;
                break;
            }
        }

        if (flag == 0)
        {
            cout << "The book title was not found." << endl;
            return;
        }

        if (books[i].getAvailability())
        {
            cout << "The book \"" << books[i].getTitle() << "\" is available at the moment. Issued to the user successfully." << endl;
            books[i].setAvailability(false);
        }
        else
        {
            cout << "Sorry! The book \"" << books[i].getTitle() << "\" is not available at the moment." << endl;
        }
    }

    void returnBook()
    {
        if (books == nullptr || num <= 0)
        {
            cout << "No books have been initialized yet." << endl;
            return;
        }

        string bookTitle;
        cin.ignore();
        cout << "Enter the title of the book you would like to return: ";
        getline(cin, bookTitle);

        int i, flag = 0;
        for (i = 0; i < num; i++)
        {
            if (bookTitle == books[i].getTitle())
            {
                flag = 1;
                break;
            }
        }

        if (flag == 0)
        {
            cout << "The book title was not found." << endl;
            return;
        }

        if (books[i].getAvailability() == false)
        {
            books[i].setAvailability(true);
            cout << "The book \"" << books[i].getTitle() << "\" has been returned successfully." << endl;
        }
        else
        {
            cout << "The book \"" << books[i].getTitle() << "\" is already available. Cannot return a book which has not been borrowed." << endl;
        }
    }

    void displayBooks()
    {
        if (books == nullptr || num <= 0)
        {
            cout << "No books have been initialized yet." << endl;
            return;
        }

        cout << endl
             << "Displaying the details of all available books:" << endl;
        for (int i = 0; i < num; i++)
        {
            cout << endl
                 << "Book " << (i + 1) << ": " << endl;
            cout << "ID: " << books[i].getID() << endl;
            cout << "Title: " << books[i].getTitle() << endl;
            cout << "Author: " << books[i].getAuthor() << endl;
            cout << "Available: " << (books[i].getAvailability() ? "Yes" : "No") << endl;
        }
    }

    ~Library()
    {
        delete[] books;
    }
};

int main()
{
    Library lib;
    int choice;
    cout << "----- Library System Menu -----" << endl;
    cout << "Enter 1 to add a book" << endl;
    cout << "Enter 2 to display all books" << endl;
    cout << "Enter 3 to borrow a book" << endl;
    cout << "Enter 4 to return a book" << endl;
    cout << "Enter 5 to exit" << endl;
    while (1) {
        cout << endl
             << "Enter your choice: " << endl;
        cin >> choice;
        switch (choice) {
        case 1:
            lib.addBook();
            break;
        case 2:
            lib.displayBooks();
            break;
        case 3:
            lib.borrowBook();
            break;
        case 4:
            lib.returnBook();
            break;
        case 5:
            cout << "Exiting the program...." << endl;
            return 0;
        }
    }
}
