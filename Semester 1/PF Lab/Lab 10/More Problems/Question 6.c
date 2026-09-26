#include <stdio.h>
#include <string.h>

struct TravelPackage {
    char packageName[50];
    char destination[50];
    int duration;
    float cost;    
    int availableSeats; 
};

void displayPackages(struct TravelPackage packages[], int size) {
    int i;
    printf("\nAvailable Travel Packages:\n");
    for (i = 0; i < size; i++) {
        printf("%d. Package Name: %s\n", i + 1, packages[i].packageName);
        printf("   Destination: %s\n", packages[i].destination);
        printf("   Duration: %d days\n", packages[i].duration);
        printf("   Cost: $%.2f\n", packages[i].cost);
        printf("   Available Seats: %d\n", packages[i].availableSeats);
        printf("\n"}; }
}

void bookPackage(struct TravelPackage packages[], int size) {
    int choice, seats_book;
    displayPackages(packages, size);
    printf("Enter the number of the package you want to book: ");
    scanf("%d", &choice);
    if (choice < 1 || choice > size) {
        printf("Invalid choice! Please try again.\n");
        return; }
    if (packages[choice - 1].availableSeats == 0) {
        printf("Sorry, no seats are available for this package.\n");
        return; }
    printf("Enter the number of seats you want to book: ");
    scanf("%d", &seats_book);
    if (seatsToBook > packages[choice - 1].availableSeats) {
        printf("Sorry, only %d seats are available. Please try again.\n", packages[choice - 1].availableSeats);
        return; }
    packages[choice - 1].availableSeats -= seatsToBook;
    printf("You have successfully booked %d seat(s) for the package '%s'.\n", seatsToBook, packages[choice - 1].packageName);
}

int main() {
    struct TravelPackage packages[3] = {
        {"Holiday in Paris", "Paris", 7, 1500.00, 10},
        {"Beach Vacation", "Hawaii", 5, 1200.00, 5},
        {"Adventure Tour", "Mount Everest", 10, 2500.00, 2}
    };
    int choice;
    while (1) {
        printf("\nTravel Package Booking System\n");
        printf("1. Display Available Packages\n");
        printf("2. Book a Package\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        if (choice == 1) {
            // Display available packages
            displayPackages(packages, 3); }
        else if (choice == 2) {
            bookPackage(packages, 3); }
        else if (choice == 3) {
            printf("Thank you for using the Travel Package Booking System.\n");
            return 0; }
        else {
            printf("Invalid choice. Please try again.\n"); } }
    return 0;
}
