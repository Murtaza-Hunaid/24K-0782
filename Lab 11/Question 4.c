#include <stdio.h>

struct Marks {
    int maths;
    int science;
    int english;
};

struct Student {
    int roll_no;
    char name[50];
    struct Marks marks;
};

int main() {
    struct Student students[5];
    int i;
    float average;
    for (i = 0; i < 5; i++) {
        printf("Enter details for student %d:\n", i + 1);
        printf("Roll No: ");
        scanf("%d", &students[i].roll_no);
        printf("Name: ");
        scanf(" %[^\n]", students[i].name); // Read string with spaces
        printf("Marks in Maths: ");
        scanf("%d", &students[i].marks.maths);
        printf("Marks in Science: ");
        scanf("%d", &students[i].marks.science);
        printf("Marks in English: ");
        scanf("%d", &students[i].marks.english);
        printf("\n"); }
    printf("Average marks for each student:\n");
    for (i = 0; i < 5; i++) {
        average = (students[i].marks.maths + students[i].marks.science + students[i].marks.english) / 3.0;
        printf("Student %d (%s): %.2f\n", students[i].roll_no, students[i].name, average); }
    return 0;
}
