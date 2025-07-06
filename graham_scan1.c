/**
 * @file graham_scan1.c
 * @brief Implementation of sorting algorithms and geometric utilities
 * @author RANARA, Ramil Carlos, SIA, Justin Michael, TIU, Avram Nathaniel - Programmer
 * @date 7/6/2025 
 * @version 1.0
 */

#include "graham_scan.h"
#include "stack.h"
#include "sort.h"

/* Purpose: Validate that there are enough points for convex hull computation
   Returns: 1 if sufficient points (>= 3), 0 otherwise
   @param currentPoints (long int): Number of input points
   Pre-condition:
   - currentPoints should be non-negative */
int checkPoints(long int currentPoints) {
    if (currentPoints >= 3) {
        return 1;
    }

    return 0;
}

/* Purpose: Initialize the convex hull with the first three sorted points
   Returns: void
   @param hull (Stack*): Pointer to the hull stack
   @param points (Point[]): Array of points sorted by polar angle
   Pre-condition:
   - points[0] is anchor point
   - points are sorted by polar angle from anchor
   - hull must point to valid, initialized Stack structure
   - points array must have at least 3 elements
   Post-condition:
   - hull stack contains the first three points */
void initialPush(Stack *hull, Point points[]) {
    PUSH(hull, points[0]);
    PUSH(hull, points[1]);
    PUSH(hull, points[2]);
}

/* Purpose: Calculate elapsed time between two clock measurements
   Returns: Elapsed time as double precision value
   @param start (clock_t): Starting clock time
   @param end (clock_t): Ending clock time
   Pre-condition:
   - start and end must be valid clock_t values
   - end should be >= start for meaningful result */
double calculateTime(clock_t start, clock_t end) {
    return (double)(end - start);
}

/* Purpose: Compute convex hull using Graham scan with bubble sort
   Returns: void
   @param hull (Stack*): Pointer to stack that will store the convex hull vertices
   @param points (Point[]): Array of input points
   @param currentPoints (long int): Number of points in the input array
   Pre-condition:
   - hull must point to valid, initialized Stack structure
   - points array must contain valid Point structures
   - currentPoints must be >= 3 for meaningful convex hull
   Post-condition:
   - hull contains the convex hull vertices in counterclockwise order
   - Timing information is printed to stdout */
void bubbleGraham(Stack *hull, Point points[], long int currentPoints) {
    if (checkPoints(currentPoints)) {

        clock_t start, end;
        double duration;
    
        start = clock();
        anchorToIndexZero(points, currentPoints);
        bubbleSort(points, currentPoints, points[0]);

        initialPush(hull, points);

        for (long int i = 3; i < currentPoints; i++) {

            while (hull->top >= 1 && orientation(NEXT_TO_TOP(hull), TOP(hull), points[i]) != -1) {
                POP(hull);
            }

            PUSH(hull, points[i]);
        }

        end = clock();
        duration = calculateTime(start, end);

        printf("Bubble Graham:\nInput Size: %6ld\nElapsed Time: %15lf\n", currentPoints, duration);

    }
}