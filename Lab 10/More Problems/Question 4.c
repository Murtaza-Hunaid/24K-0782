#include <stdio.h>
#include <string.h>

struct Book {
    char title[100];
    char author[100];
    int publication_year;
    float price;
};

void displayBooks(struct Book books[], int count);
void searchByTitle(struct Book books[], int count, char title[]);
void listByAuthor(struct Book books[], int count, char author[]);

int main() {
    int book_count, i;
    printf("Enter the number of books: ");
    scanf("%d", &book_count);
    getchar(); 
    struct Book library[book_count];
    for (i = 0; i < book_count; i++) {
        printf("\nEnter details for book %d:\n", i + 1);   
        printf("Enter title: ");
        fgets(library[i].title, sizeof(library[i].title), stdin);
        library[i].title[strcspn(library[i].title, "\n")] = '\0';
        printf("Enter author: ");
        fgets(library[i].author, sizeof(library[i].author), stdin);
        library[i].author[strcspn(library[i].author, "\n")] = '\0'; 
        printf("Enter publication year: ");
        scanf("%d", &library[i].publication_year);
        getchar(); 
        printf("Enter price: ");
        scanf("%f", &library[i].price);
        getchar(); }
    printf("\nAll Books:\n");
    displayBooks(library, book_count);
    char search_title[100];
    printf("\nEnter the title of the book to search: ");
    fgets(search_title, sizeof(search_title), stdin);
    search_title[strcspn(search_title, "\n")] = '\0'; 
    searchByTitle(library, book_count, search_title);
    char search_author[100];
    printf("\nEnter the author to list their books: ");
    fgets(search_author, sizeof(search_author), stdin);
    search_author[strcspn(search_author, "\n")] = '\0'; 
    listByAuthor(library, book_count, search_author);
    return 0;
}

void displayBooks(struct Book books[], int count) {
    for (int i = 0; i < count; i++) {
        printf("Title: %s\nAuthor: %s\nPublication Year: %d\nPrice: $%.2f\n\n",
               books[i].title, books[i].author, books[i].publication_year, books[i].price); }
}

void searchByTitle(struct Book books[], int count, char title[]) {
    int found = 0, i;
    for (i = 0; i < count; i++) {
        if (strcmp(books[i].title, title) == 0) {
            printf("\nBook Found:\nTitle: %s\nAuthor: %s\nPublication Year: %d\nPrice: $%.2f\n",
                   books[i].title, books[i].author, books[i].publication_year, books[i].price);
            found = 1;
            break; } }
    if (!found) {
        printf("\nBook with title '%s' not found.\n", title); } }

void listByAuthor(struct Book books[], int count, char author[]) {
    int found = 0;
    printf("\nBooks by %s:\n", author);
    for (int i = 0; i < count; i++) {
        if (strcmp(books[i].author, author) == 0) {
            printf("Title: %s\nPublication Year: %d\nPrice: $%.2f\n\n",
                   books[i].title, books[i].publication_year, books[i].price);
            found = 1; } }
    if (!found) {
        printf("No books found by author '%s'.\n", author); }
}
