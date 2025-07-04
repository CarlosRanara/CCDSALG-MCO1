/* ============================================================================
 * FILE: graham_scan2.c
 * Graham Scan Algorithm with Fast Sorting (Merge Sort)
 * Programmer: [Your Name]
 * Tester: [Your Name]
 * ============================================================================ */
#include <stdio.h>
#include <time.h>
#include "stack.h"
#include "sort.h"

/* Local cross product function for Graham Scan - different from sorting cross product */
double computeCrossProductLocal(pointType p1, pointType p2, pointType p3)
{
    return (p2.x - p1.x) * (p3.y - p1.y) - (p2.y - p1.y) * (p3.x - p1.x);
}

/* Graham Scan algorithm implementation using fast sorting */
/* Graham Scan algorithm implementation using fast sorting - no break */
int grahamScan2(pointType points[], int nSize, pointType result[])
{
    stackType hull;
    pointType anchor;
    int i, nMinIndex, nHullSize;
    clock_t start, end;
    double dElapsedTime;

    /* Handle edge cases */
    if (nSize == 0)
    {
        return 0;
    }

    if (nSize == 1)
    {
        result[0] = points[0];
        return 1;
    }

    if (nSize == 2)
    {
        result[0] = points[0];
        result[1] = points[1];
        return 2;
    }

    start = clock();

    /* Find anchor point (lowest y coordinate, then lowest x coordinate) */
    nMinIndex = 0;
    for (i = 1; i < nSize; i++)
    {
        if (points[i].y < points[nMinIndex].y ||
            (points[i].y == points[nMinIndex].y && points[i].x < points[nMinIndex].x))
        {
            nMinIndex = i;
        }
    }

    /* Move anchor to first position */
    anchor = points[nMinIndex];
    points[nMinIndex] = points[0];
    points[0] = anchor;

    /* Sort remaining points by polar angle using merge sort */
    mergeSort(&points[1], nSize - 1, anchor);

    /* Initialize stack and push first two points */
    createStack(&hull);
    pushStack(&hull, points[0]);
    pushStack(&hull, points[1]);

    /* Process remaining points starting from index 2 */
    for (i = 2; i < nSize; i++)
    {
        /* Remove points that make clockwise turn or are collinear */
        while (hull.nTop > 0 && 
               computeCrossProductLocal(nextToTopStack(&hull), topStack(&hull), points[i]) <= 0.0)
        {
            popStack(&hull);
        }
        pushStack(&hull, points[i]);
    }

    /* Copy hull points to result array */
    nHullSize = hull.nTop + 1;
    for (i = 0; i <= hull.nTop; i++)
    {
        result[i] = hull.data[i];
    }

    end = clock();
    dElapsedTime = ((double)(end - start)) / CLOCKS_PER_SEC * 1000.0;
    printf("Graham Scan (Merge Sort) execution time: %.3f milliseconds\n", dElapsedTime);

    return nHullSize;
}