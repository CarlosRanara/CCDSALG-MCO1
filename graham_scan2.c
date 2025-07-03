/* ============================================================================
 * FILE: graham_scan2.c  
 * Graham Scan Algorithm with Fast Sorting - Fully C99 Procedural Compliant
 * Programmer: [Your Name]
 * Tester: [Your Name]
 * ============================================================================ */
#include <stdio.h>
#include <time.h>
#include "stack.h"
#include "sort.h"

/* Local cross product function for Graham Scan */
double computeCrossProductLocal(pointType p1, pointType p2, pointType p3) {
    double dResult;
    
    dResult = (p2.x - p1.x) * (p3.y - p1.y) - (p2.y - p1.y) * (p3.x - p1.x);
    
    return dResult;
}

/* Graham Scan algorithm implementation using fast sorting */
int grahamScan2(pointType points[], int nSize, pointType result[]) {
    stackType hull;
    pointType anchor, p1, p2;
    int i, nMinIndex, nHullSize, bFoundAnchor;
    clock_t start, end;
    double dElapsedTime, dCrossProduct;
    
    /* Handle edge cases */
    if (nSize == 0) {
        nHullSize = 0;
    } else if (nSize == 1) {
        result[0] = points[0];
        nHullSize = 1;
    } else if (nSize == 2) {
        result[0] = points[0];
        result[1] = points[1];
        nHullSize = 2;
    } else {
        start = clock();
        
        /* Find anchor point (lowest y coordinate, then lowest x coordinate) */
        nMinIndex = 0;
        bFoundAnchor = 0;
        for (i = 1; i < nSize && bFoundAnchor == 0; ) {
            if (points[i].y < points[nMinIndex].y || 
               (points[i].y == points[nMinIndex].y && points[i].x < points[nMinIndex].x)) {
                nMinIndex = i;
            }
            i++;
            if (i >= nSize) {
                bFoundAnchor = 1;
            }
        }
        
        /* Move anchor to first position */
        anchor = points[nMinIndex];
        points[nMinIndex] = points[0];
        points[0] = anchor;
        
        /* Sort remaining points by polar angle using merge sort */
        mergeSort(&points[1], nSize - 1, anchor);
        
        /* Initialize stack and push first point (anchor) */
        createStack(&hull);
        pushStack(&hull, points[0]);
        pushStack(&hull, points[1]);
        
        /* Process remaining points starting from index 2 */
        for (i = 2; i < nSize; i++) {
            /* Remove points that make clockwise turn or are collinear */
            while (hull.nTop > 0) {
                p2 = topStack(&hull);
                p1 = nextToTopStack(&hull);
                dCrossProduct = computeCrossProductLocal(p1, p2, points[i]);
                if (dCrossProduct > 0.0) {
                    i = nSize; /* Break out of while loop using flag */
                } else {
                    popStack(&hull); /* Remove point that makes clockwise turn */
                }
            }
            if (i < nSize) {
                pushStack(&hull, points[i]);
            }
        }
        
        /* Copy hull points to result array */
        nHullSize = hull.nTop + 1;
        for (i = 0; i <= hull.nTop; i++) {
            result[i] = hull.data[i];
        }
        
        end = clock();
        dElapsedTime = ((double)(end - start)) / CLOCKS_PER_SEC * 1000.0;
        printf("Graham Scan (Merge Sort) execution time: %.6f milliseconds\n", dElapsedTime);
    }
    
    return nHullSize;
}