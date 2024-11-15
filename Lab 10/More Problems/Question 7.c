#include <stdio.h>

struct Date {
    int day;
    int month;
    int year;
};

int isLeapYear(int year) {
    if ((year % 400 == 0) || (year % 4 == 0 && year % 100 != 0)) {
        return 1; }
    return 0; 
}

int daysInMonth(int month, int year) {
    if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12) {
        return 31; }
    if (month == 4 || month == 6 || month == 9 || month == 11) {
        return 30; }
    if (month == 2) {
        return isLeapYear(year) ? 29 : 28; }
    return 0;
}

int isValidDate(struct Date date) {
    if (date.year < 1) return 0;
    if (date.month < 1 || date.month > 12) return 0;
    if (date.day < 1 || date.day > daysInMonth(date.month, date.year)) return 0;
    return 1; 
}

int daysBetween(struct Date date1, struct Date date2) {
    int totalDays1 = 0, totalDays2 = 0, i;
    for (i = 1; i < date1.year; i++) {
        totalDays1 += (isLeapYear(i) ? 366 : 365); }
    for (i = 1; i < date1.month; i++) {
        totalDays1 += daysInMonth(i, date1.year); }
    totalDays1 += date1.day;
    for (i = 1; i < date2.year; i++) {
        totalDays2 += (isLeapYear(i) ? 366 : 365); }
    for (i = 1; i < date2.month; i++) {
        totalDays2 += daysInMonth(i, date2.year); }
    totalDays2 += date2.day;
    return totalDays2 - totalDays1;
}

const char* dayOfWeek(struct Date date) {
    int day = date.day;
    int month = date.month;
    int year = date.year;
    if (month <= 2) {
        month += 12;
        year--; }
    int k = year % 100;
    int j = year / 100;
    int f = day + (13 * (month + 1)) / 5 + k + k / 4 + j / 4 + 5 * j;
    int dayOfWeek = f % 7;
    const char* days[7] = {"Saturday", "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday"};
    return days[dayOfWeek];
}

int main() {
    struct Date date1, date2;
    printf("Enter first date (day month year): ");
    scanf("%d %d %d", &date1.day, &date1.month, &date1.year);
    printf("Enter second date (day month year): ");
    scanf("%d %d %d", &date2.day, &date2.month, &date2.year);
    if (!isValidDate(date1)) {
        printf("Invalid first date\n");
        return 0; }
    if (!isValidDate(date2)) {
        printf("Invalid second date\n");
        return 0; }
    int daysDiff = daysBetween(date1, date2);
    printf("Number of days between the two dates: %d\n", daysDiff);
    printf("Day of the week for the first date: %s\n", dayOfWeek(date1));
    return 0;
}
