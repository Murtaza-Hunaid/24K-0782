#include <stdio.h>
#include <math.h>
struct Point {
    float x;
    float y;
};

float calculateDistance(struct Point p1, struct Point p2) {
    return sqrt((p2.x - p1.x) * (p2.x - p1.x) + (p2.y - p1.y) * (p2.y - p1.y));
}

int isWithinRectangle(struct Point p, struct Point bottomLeft, struct Point topRight) {
    return (p.x >= bottomLeft.x && p.x <= topRight.x && p.y >= bottomLeft.y && p.y <= topRight.y);
}

int main() {
    struct Point p1, p2, testPoint, rectBottomLeft, rectTopRight;
    printf("Enter coordinates of first point (x y): ");
    scanf("%f %f", &p1.x, &p1.y);
    printf("Enter coordinates of second point (x y): ");
    scanf("%f %f", &p2.x, &p2.y);
    printf("Distance between points: %.2f\n", calculateDistance(p1, p2));
    printf("Enter coordinates of the point to check (x y): ");
    scanf("%f %f", &testPoint.x, &testPoint.y);
    printf("Enter coordinates of bottom-left corner of the rectangle (x y): ");
    scanf("%f %f", &rectBottomLeft.x, &rectBottomLeft.y);
    printf("Enter coordinates of top-right corner of the rectangle (x y): ");
    scanf("%f %f", &rectTopRight.x, &rectTopRight.y);
    if (isWithinRectangle(testPoint, rectBottomLeft, rectTopRight)) {
        printf("The point (%.2f, %.2f) lies within the rectangular boundary.\n", testPoint.x, testPoint.y); } 
    else {
        printf("The point (%.2f, %.2f) does not lie within the rectangular boundary.\n", testPoint.x, testPoint.y); }
}
