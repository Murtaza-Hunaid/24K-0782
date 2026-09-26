#include <stdio.h>

struct Date {
    int day;
    int month;
    int year;
};

struct Event {
    char event_name[100];
    struct Date date;
    char location[100];
};

int main() {
    struct Event events[3]; 
    int i;
    for (i = 0; i < 3; i++) {
        printf("Enter details for event %d:\n", i + 1);
        printf("Event Name: ");
        scanf(" %[^\n]", events[i].event_name); 
        printf("Event Date (dd mm yyyy): ");
        scanf("%d %d %d", &events[i].date.day, &events[i].date.month, &events[i].date.year);
        printf("Event Location: ");
        scanf(" %[^\n]", events[i].location);
        printf("\n"); }
    printf("Event Details:\n");
    for (i = 0; i < 3; i++) {
        printf("Event %d:\n", i + 1);
        printf("Name: %s\n", events[i].event_name);
        printf("Date: %02d/%02d/%04d\n", events[i].date.day, events[i].date.month, events[i].date.year);
        printf("Location: %s\n\n", events[i].location); }
    return 0;
}
