/* ============================================================================
 * FILE: sort.c
 * Sorting Algorithms Implementation - Fully C99 Procedural Compliant
 * Programmer: [Your Name]
 * Tester: [Your Name]
 * ============================================================================ */
#include "sort.h"
#include <stdio.h>

/* Computes polar angle from anchor to point without using math.h */
double computePolarAngle(pointType anchor, pointType point) {
    double dDx, dDy, dAngle;
    
    dDx = point.x - anchor.x;
    dDy = point.y - anchor.y;
    
    /* Handle special cases */
    if (dDx == 0.0 && dDy == 0.0) {
        dAngle = 0.0;
    } else if (dDx == 0.0) {
        if (dDy > 0.0) {
            dAngle = 1.5707963268; /* PI/2 */
        } else {
            dAngle = -1.5707963268; /* -PI/2 */
        }
    } else if (dDy == 0.0) {
        if (dDx > 0.0) {
            dAngle = 0.0; /* 0 degrees */
        } else {
            dAngle = 3.1415926536; /* PI */
        }
    } else if (dDx > 0.0 && dDy > 0.0) {
        /* First quadrant */
        dAngle = dDy / dDx;
    } else if (dDx < 0.0 && dDy > 0.0) {
        /* Second quadrant */
        dAngle = 3.1415926536 + dDy / dDx;
    } else if (dDx < 0.0 && dDy < 0.0) {
        /* Third quadrant */
        dAngle = 3.1415926536 - dDy / dDx;
    } else {
        /* Fourth quadrant */
        dAngle = 6.2831853072 + dDy / dDx;
    }
    
    return dAngle;
}

/* Computes squared distance between two points */
double computeDistanceSquared(pointType p1, pointType p2) {
    double dDx, dDy, dResult;
    
    dDx = p2.x - p1.x;
    dDy = p2.y - p1.y;
    dResult = dDx * dDx + dDy * dDy;
    
    return dResult;
}

/* Compares two points based on polar angle with respect to anchor */
int comparePointsByAngle(pointType p1, pointType p2, pointType anchor) {
    double dCrossProduct, dDist1, dDist2;
    int nResult;
    
    /* Use cross product to determine orientation */
    dCrossProduct = (p1.x - anchor.x) * (p2.y - anchor.y) - (p1.y - anchor.y) * (p2.x - anchor.x);
    
    if (dCrossProduct > 0.0) {
        nResult = -1; /* p1 comes before p2 (counterclockwise) */
    } else if (dCrossProduct < 0.0) {
        nResult = 1;  /* p2 comes before p1 */
    } else {
        /* If collinear, compare by distance from anchor */
        dDist1 = computeDistanceSquared(anchor, p1);
        dDist2 = computeDistanceSquared(anchor, p2);
        
        if (dDist1 < dDist2) {
            nResult = -1; /* Closer point comes first */
        } else if (dDist1 > dDist2) {
            nResult = 1;
        } else {
            nResult = 0; /* Same point */
        }
    }
    
    return nResult;
}

/* Swaps two points */
void swapPoints(pointType *p1, pointType *p2) {
    pointType temp;
    
    temp = *p1;
    *p1 = *p2;
    *p2 = temp;
}

/* Bubble Sort - Slow sorting algorithm O(n^2) */
void bubbleSort(pointType points[], int nSize, pointType anchor) {
    int i, j, bSwapped, nComparison;
    
    for (i = 0; i < nSize - 1; i++) {
        bSwapped = 0;
        for (j = 0; j < nSize - i - 1; j++) {
            nComparison = comparePointsByAngle(points[j], points[j + 1], anchor);
            if (nComparison > 0) {
                swapPoints(&points[j], &points[j + 1]);
                bSwapped = 1;
            }
        }
        /* If no swapping occurred, array is sorted */
        if (bSwapped == 0) {
            i = nSize; /* Exit loop using flag instead of break */
        }
    }
}

/* Merge function for Merge Sort */
void mergeArrays(pointType points[], int nLeft, int nMid, int nRight, pointType anchor) {
    pointType leftArray[16384], rightArray[16384];
    int nLeftSize, nRightSize, i, j, k, nComparison;
    
    nLeftSize = nMid - nLeft + 1;
    nRightSize = nRight - nMid;
    
    /* Check array bounds to prevent overflow */
    if (nLeftSize > 16384 || nRightSize > 16384) {
        printf("Error: Array size too large for merge operation\n");
    } else {
        /* Copy data to temporary arrays */
        for (i = 0; i < nLeftSize; i++) {
            leftArray[i] = points[nLeft + i];
        }
        for (j = 0; j < nRightSize; j++) {
            rightArray[j] = points[nMid + 1 + j];
        }
        
        /* Merge the temporary arrays back into points[nLeft..nRight] */
        i = 0;
        j = 0;
        k = nLeft;
        
        while (i < nLeftSize && j < nRightSize) {
            nComparison = comparePointsByAngle(leftArray[i], rightArray[j], anchor);
            if (nComparison <= 0) {
                points[k] = leftArray[i];
                i++;
            } else {
                points[k] = rightArray[j];
                j++;
            }
            k++;
        }
        
        /* Copy remaining elements of leftArray[], if any */
        while (i < nLeftSize) {
            points[k] = leftArray[i];
            i++;
            k++;
        }
        
        /* Copy remaining elements of rightArray[], if any */
        while (j < nRightSize) {
            points[k] = rightArray[j];
            j++;
            k++;
        }
    }
}

/* Merge Sort recursive helper function */
void mergeSortHelper(pointType points[], int nLeft, int nRight, pointType anchor) {
    int nMid;
    
    if (nLeft < nRight) {
        nMid = nLeft + (nRight - nLeft) / 2;
        mergeSortHelper(points, nLeft, nMid, anchor);
        mergeSortHelper(points, nMid + 1, nRight, anchor);
        mergeArrays(points, nLeft, nMid, nRight, anchor);
    }
}

/* Merge Sort - Fast sorting algorithm O(n log n) */
void mergeSort(pointType points[], int nSize, pointType anchor) {
    if (nSize > 1) {
        mergeSortHelper(points, 0, nSize - 1, anchor);
    }
}