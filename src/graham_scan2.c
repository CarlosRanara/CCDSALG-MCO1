/**
 * graham_scan2.c
 * Implementation of Graham's Scan algorithm using merge sort (fast version)
 * Group 16 Assignment: Merge Sort (fast algorithm)
 * CCDSALG Term 3, AY 2024-2025
 */

#include "graham_scan.h"

void copyPointsArray(Point src[], Point dest[], int n) {
    int i;
    
    i = 0;
    while (i < n) {
        dest[i] = src[i];
        i++;
    }
}

void processPointsForHull(Point points[], int n, Point hull[], int *hullSize) {
    Stack hullStack;
    int nStackSize;
    int bSuccess;
    int nOrientation;
    Point pTopPoint;
    Point pNextToTopPoint;
    Point pCurrentPoint;
    int i;
    int j;
    int bContinuePopping;
    
    /* Create a stack for the convex hull */
    createStack(&hullStack);
    
    /* Push the first three points to the stack */
    pushToStack(&hullStack, points[0], &bSuccess);
    pushToStack(&hullStack, points[1], &bSuccess);
    pushToStack(&hullStack, points[2], &bSuccess);
    
    /* Process the remaining points */
    i = 3;
    while (i < n) {
        /* Keep popping while the angle formed by the top three points makes a non-left turn */
        bContinuePopping = 1;
        while (getStackSize(&hullStack) > 1 && bContinuePopping) {
            getTopOfStack(&hullStack, &pTopPoint, &bSuccess);
            getNextToTopOfStack(&hullStack, &pNextToTopPoint, &bSuccess);
            calculateOrientation(pNextToTopPoint, pTopPoint, points[i], &nOrientation);
            
            if (nOrientation != 2) {
                popFromStack(&hullStack, &pTopPoint, &bSuccess);
            } else {
                bContinuePopping = 0;
            }
        }
        
        /* Push the current point to the hull */
        pushToStack(&hullStack, points[i], &bSuccess);
        i++;
    }
    
    /* Transfer the stack contents to the hull array */
    nStackSize = getStackSize(&hullStack);
    
    j = nStackSize - 1;
    while (j >= 0) {
        popFromStack(&hullStack, &pCurrentPoint, &bSuccess);
        hull[j] = pCurrentPoint;
        j--;
    }
    
    *hullSize = nStackSize;
}

void grahamScanFast(Point points[], int n, Point hull[], int *hullSize) {
    int i;
    clock_t tStart;
    clock_t tEnd;
    double tElapsed;
    Point pointsCopy[MAX_STACK_SIZE];
    int nAnchorIndex;
    
    /* Start the timer */
    tStart = clock();
    
    /* Create a copy of the points to avoid modifying the original array */
    copyPointsArray(points, pointsCopy, n);
    
    /* Find the anchor point (lowest y-coordinate, leftmost if tie) */
    findAnchorPoint(pointsCopy, n, &nAnchorIndex);
    
    /* Sort points by polar angle with respect to anchor point using merge sort */
    mergeSortPoints(pointsCopy, n, nAnchorIndex);
    
    /* If there are fewer than 3 points, convex hull is the points themselves */
    if (n < 3) {
        i = 0;
        while (i < n) {
            hull[i] = pointsCopy[i];
            i++;
        }
        
        *hullSize = n;
    } else {
        /* Process the points to find the convex hull */
        processPointsForHull(pointsCopy, n, hull, hullSize);
    }
    
    /* End the timer and display elapsed time */
    tEnd = clock();
    tElapsed = ((double)(tEnd - tStart)) / CLOCKS_PER_SEC * 1000; /* Convert to milliseconds */
    printf("Graham's Scan (Merge Sort) execution time: %.6f milliseconds\n", tElapsed);
}
