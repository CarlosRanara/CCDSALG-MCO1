#include "graham_scan.h"

// Typedef for char array for storing the names of input and output files as a string.
typedef char String20[21];

void askFileNames(String20 inputName, String20 outputName) {
    printf("Filename of Source File (with .TXT extension): ");
    fscanf(stdin, "%s", inputName);
    printf("Filename of Destination File (with .TXT extension): ");
    fscanf(stdin, "%s", outputName);
}

void setFilePointers(String20 inputName, String20 outputName, FILE **src, FILE **dest) {
    *src = fopen(inputName, "r");
    *dest = fopen(outputName, "w");

    if (NULL == *src) {
        fprintf(stderr, "ERROR: FILE NOT FOUND\n");
        fclose(*dest);
    }
}

void readFileContent(FILE *src, Point points[], long int *currentPoints) {
    fscanf(src, "%ld", currentPoints);

    for (long int i = 0; i < *currentPoints; i++) {
        fscanf(src, "%lf %lf", &points[i].x, &points[i].y);
    }
}

void printHull(Stack *hull, FILE *dest) {
    fprintf(dest, "%ld\n", hull->top+1);

    for (long int i = 0; i <= hull->top; i++) {
        fprintf(dest, "%.06lf\t%.06lf\n", hull->arr[i].x, hull->arr[i].y);
    }

}

void verifyEnoughPoints(long int currentPoints, FILE *dest, Stack *hull, Point *points) {
    if (currentPoints >= 3) {
        mergeGraham(hull, points, currentPoints);
        printHull(hull, dest);
    }

    else {
        fprintf(dest, "WARNING: Not enough points to make convex hull");
    }
}

int main () {
    FILE *src, *dest;
    Stack hull;
    Point points[MAX];
    String20 inputName, outputName;
    long int currentPoints;

    CREATE(&hull);

    askFileNames(inputName, outputName);
    setFilePointers(inputName, outputName, &src, &dest);

    if (src != NULL) {
        readFileContent(src, points, &currentPoints);
        verifyEnoughPoints(currentPoints, dest, &hull, points);

        fflush(src);
        fflush(dest);
        fclose(src);
        fclose(dest);
    }

    return 0;
}