#include <iostream>
#include <string>

using namespace std;

class Media {
protected:
    string title;
    string publicationDate;
    string uniqueID;
    string publisher;
    bool isAvailable;

public:
    Media(string t, string pd, string uid, string pub) : title(t), publicationDate(pd), uniqueID(uid), publisher(pub), isAvailable(true) {}

    virtual void displayInfo() {
        cout << "Title: " << title << endl;
        cout << "Publication Date: " << publicationDate << endl;
        cout << "Unique ID: " << uniqueID << endl;
        cout << "Publisher: " << publisher << endl;
        cout << "Available: " << (isAvailable ? "Yes" : "No") << endl;
    }

    void checkOut() {
        if (isAvailable) {
            isAvailable = false;
            cout << "Checked out: " << title << endl; } 
		else {
            cout << title << " is not available." << endl; }
    }

    void returnItem() {
        isAvailable = true;
        cout << "Returned: " << title << endl;
    }

    string getTitle() {
        return title;
    }

    string getPublicationDate() {
        return publicationDate;
    }
};

class Book : public Media {
private:
    string author;
    string ISBN;
    int numberOfPages;

public:
    Book(string t, string pd, string uid, string pub, string a, string isbn, int pages) : Media(t, pd, uid, pub), author(a), ISBN(isbn), numberOfPages(pages) {}

    void displayInfo() {
        Media::displayInfo();
        cout << "Author: " << author << endl;
        cout << "ISBN: " << ISBN << endl;
        cout << "Pages: " << numberOfPages << endl;
    }

    string getAuthor() {
        return author;
    }
};

class DVD : public Media {
private:
    string director;
    int duration;
    string rating;

public:
    DVD(string t, string pd, string uid, string pub, string dir, int dur, string rate) : Media(t, pd, uid, pub), director(dir), duration(dur), rating(rate) {}

    void displayInfo() {
        Media::displayInfo();
        cout << "Director: " << director << endl;
        cout << "Duration: " << duration << " mins" << endl;
        cout << "Rating: " << rating << endl;
    }
};

class CD : public Media {
private:
    string artist;
    int numberOfTracks;
    string genre;

public:
    CD(string t, string pd, string uid, string pub, string art, int tracks, string gen) : Media(t, pd, uid, pub), artist(art), numberOfTracks(tracks), genre(gen) {}

    void displayInfo() {
        Media::displayInfo();
        cout << "Artist: " << artist << endl;
        cout << "Tracks: " << numberOfTracks << endl;
        cout << "Genre: " << genre << endl;
    }
};

class Magazine : public Media {
private:
    int issueNumber;

public:
    Magazine(string t, string pd, string uid, string pub, int issue) : Media(t, pd, uid, pub), issueNumber(issue) {}

    void displayInfo() {
        Media::displayInfo();
        cout << "Issue Number: " << issueNumber << endl;
    }
};

void searchMediaByTitle(Media *media[], int size, string searchTitle) {
    for (int i = 0; i < size; i++) {
        if (media[i]->getTitle() == searchTitle) {
            media[i]->displayInfo(); } }
}

void searchMediaByPublicationDate(Media *media[], int size, string searchDate) {
    for (int i = 0; i < size; i++) {
        if (media[i]->getPublicationDate() == searchDate) {
            media[i]->displayInfo(); } }
}

void searchBookByAuthor(Book *books[], int size, string searchAuthor) {
    for (int i = 0; i < size; i++) {
        if (books[i]->getAuthor() == searchAuthor) {
            books[i]->displayInfo(); } }
}

int main() {
    Book b1("C++ Basics", "2020", "B001", "TechPress", "John Doe", "123456789", 350);
    DVD d1("The Matrix", "1999", "D001", "Warner Bros", "Wachowskis", 136, "R");
    CD c1("Thriller", "1982", "C001", "Epic", "Michael Jackson", 9, "Pop");
    Magazine m1("National Geographic", "2023", "M001", "NatGeo", 145);
    Media *mediaList[4] = { &b1, &d1, &c1, &m1 };
    Book *bookList[1] = { &b1 };
    b1.checkOut();
    b1.returnItem();
    cout << endl << "Search by Title: " << endl;
    searchMediaByTitle(mediaList, 4, "C++ Basics");
    cout << endl << "Search by Publication Date: " << endl;
    searchMediaByPublicationDate(mediaList, 4, "1999");
    cout << endl << "Search Book by Author: " << endl;
    searchBookByAuthor(bookList, 1, "John Doe");
    return 0;
}
