#include "graham_scan.h"

/*
@file main1.c
@Driver file for grahan algorithm with bubble sort.
@author RANARA, Ramil Carlos, SIA, Justin Michael, TIU, Avram Nathaniel - Programmer
@date 7/6/2025
@version 1.0
*/

// Typedef for char array for storing the names of input and output files as a string.
typedef char String20[21];

/*
Purpose: Asks for user input for the name of the source and destination files.
Returns: void
@param inputName: Array of char that stores the filename of source.
@param outputName: Array of char that stores the filename of destination.
*/
void askFileNames(String20 inputName, String20 outputName) {
    printf("Filename of Source File (with .TXT extension): ");
    fscanf(stdin, "%s", inputName);
    printf("Filename of Destination File (with .TXT extension): ");
    fscanf(stdin, "%s", outputName);
}

/*
Purpose: Sets the file pointers to point to the source and destination files.
Returns: void
@param inputName: Array of char that stores the filename of source.
@param outputName: Array of char that stores the filename of destination.
@param src: File pointer pointing to source file.
@param dest: File pointer pointing to destination file.
*/
void setFilePointers(String20 inputName, String20 outputName, FILE **src, FILE **dest) {
    *src = fopen(inputName, "r");
    *dest = fopen(outputName, "w");

    // If src does not exist, close dest pointer
    if (NULL == *src) {
        fprintf(stderr, "ERROR: FILE NOT FOUND\n");
        fclose(*dest);
    }
}

/*
Purpose: Read contents from source file and transfer to points array
Returns: void
@param src: File pointer that points to the source file.
@param points: Array of points holding the different point entries from source.
@param currentPoints: Current number of points received from source file.
Pre-condition:  
        - Source file must exactly have two columns of entries for this program to work as intended.
*/
void readFileContent(FILE *src, Point points[], long int *currentPoints) {
    fscanf(src, "%ld", currentPoints);

    for (long int i = 0; i < *currentPoints; i++) {
        fscanf(src, "%lf %lf", &points[i].x, &points[i].y);
    }
}

/*
Purpose: Print the contents of the convex hull into destination file.
Returns: void
@param hull: Stack containing the different points for convex hull.
@param dest: File pointer that points to the source file.
Pre-condition:  
        - Source file must exactly have two columns of entries for this program to work as intended.
*/
void printHull(Stack *hull, FILE *dest) {
    fprintf(dest, "%ld\n", hull->top+1);

    for (long int i = 0; i <= hull->top; i++) {
        fprintf(dest, "%.06lf\t%.06lf\n", hull->arr[i].x, hull->arr[i].y);
    }

}

/*
Purpose: Checks if there are enough points to make the hull before construction.
Returns: void
@param currentPoints: The number of points obtained from source file.
@param dest: File pointer to destination file.
@param hull: Stack containing the points for convex hull.
@param points: Array containing the points from source file.
*/
void verifyEnoughPoints(long int currentPoints, FILE *dest, Stack *hull, Point *points) {
    if (currentPoints >= 3) {
        bubbleGraham(hull, points, currentPoints);
        printHull(hull, dest);
    }

    // If there's not enough points, destination file will receive this string.
    else {
        fprintf(dest, "WARNING: Not enough points to make convex hull");
    }
}

/*
Purpose: Main function for the program to run and executes the different functions.
Returns: 0 for program termination.
*/
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