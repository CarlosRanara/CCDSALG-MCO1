/* ============================================================================
 * FILE: sort.c
 * Sorting Algorithms Implementation
 * Programmer: [Your Name]
 * Tester: [Your Name]
 * ============================================================================ */
#include "sort.h"
#include <stdio.h>

/* Improved polar angle computation using atan2 approximation */
double computePolarAngle(pointType anchor, pointType point)
{
    double dDx, dDy;
    
    dDx = point.x - anchor.x;
    dDy = point.y - anchor.y;
    
    /* Handle special cases */
    if (dDx == 0.0 && dDy == 0.0)
    {
        return 0.0;
    }
    
    /* Use a simplified atan2 approximation */
    if (dDx == 0.0)
    {
        return (dDy > 0.0) ? 1.5707963268 : -1.5707963268; /* ±PI/2 */
    }
    
    if (dDy == 0.0)
    {
        return (dDx > 0.0) ? 0.0 : 3.1415926536; /* 0 or PI */
    }
    
    /* Simple atan approximation for each quadrant */
    double ratio = dDy / dDx;
    double angle;
    
    if (dDx > 0.0)
    {
        /* First and fourth quadrants */
        angle = ratio / (1.0 + 0.28 * ratio * ratio);
        if (angle < 0.0) angle += 6.2831853072; /* 2*PI */
    }
    else
    {
        /* Second and third quadrants */
        angle = 3.1415926536 + ratio / (1.0 + 0.28 * ratio * ratio);
    }
    
    return angle;
}

/* Computes squared distance between two points */
double computeDistanceSquared(pointType p1, pointType p2)
{
    double dDx, dDy;
    dDx = p2.x - p1.x;
    dDy = p2.y - p1.y;
    return dDx * dDx + dDy * dDy;
}

/* Compares two points based on polar angle with respect to anchor */
int comparePointsByAngle(pointType p1, pointType p2, pointType anchor)
{
    double dCrossProduct, dDist1, dDist2;

    /* Use cross product to determine orientation */
    /* Cross product of vectors (anchor->p1) and (anchor->p2) */
    dCrossProduct = (p1.x - anchor.x) * (p2.y - anchor.y) - (p1.y - anchor.y) * (p2.x - anchor.x);

    if (dCrossProduct > 0.0)
    {
        return -1; /* p1 comes before p2 (counterclockwise) */
    }
    if (dCrossProduct < 0.0)
    {
        return 1; /* p2 comes before p1 */
    }

    /* If collinear, compare by distance from anchor */
    dDist1 = computeDistanceSquared(anchor, p1);
    dDist2 = computeDistanceSquared(anchor, p2);

    if (dDist1 < dDist2)
    {
        return -1; /* Closer point comes first */
    }
    if (dDist1 > dDist2)
    {
        return 1;
    }

    return 0; /* Same point */
}

/* Swaps two points */
void swapPoints(pointType *p1, pointType *p2)
{
    pointType temp;
    temp = *p1;
    *p1 = *p2;
    *p2 = temp;
}

/* Bubble Sort - Slow sorting algorithm O(n^2) */
void bubbleSort(pointType points[], int nSize, pointType anchor)
{
    int i, j, bSwapped, bFlag = 1;

    for (i = 0; i < nSize - 1 && bFlag; i++)
    {
        bSwapped = 0;
        for (j = 0; j < nSize - i - 1; j++)
        {
            if (comparePointsByAngle(points[j], points[j + 1], anchor) > 0)
            {
                swapPoints(&points[j], &points[j + 1]);
                bSwapped = 1;
            }
        }
        /* If no swapping occurred, array is sorted */
        if (bSwapped == 0)
        {
            bFlag = 0;
        }
    }
}

/* Merge Sort - Fast sorting algorithm O(n log n) */
void mergeSort(pointType points[], int nSize, pointType anchor)
{
    int nCurrentSize, nLeft;
    int bStop = 0;

    if (!(nSize <= 1))
    {
        /* Use iterative merge sort to avoid stack overflow with large datasets */
        for (nCurrentSize = 1; nCurrentSize < nSize; nCurrentSize = 2 * nCurrentSize)
        {
            bStop = 0;
            for (nLeft = 0; nLeft < nSize - 1 && !bStop; nLeft += 2 * nCurrentSize)
            {
                int nMid = nLeft + nCurrentSize - 1;
                int nRight = nLeft + 2 * nCurrentSize - 1;

                if (nMid >= nSize)
                {
                    bStop = 1;
                }
                else
                {
                    if (nRight >= nSize)
                    {
                        nRight = nSize - 1;
                    }
                    mergeArrays(points, nLeft, nMid, nRight, anchor);
                }
            }
        }
    }
}

/* Merge Sort recursive helper function - kept for compatibility but not used */
void mergeSortHelper(pointType points[], int nLeft, int nRight, pointType anchor)
{
    int nMid;

    if (nLeft < nRight)
    {
        nMid = nLeft + (nRight - nLeft) / 2;
        mergeSortHelper(points, nLeft, nMid, anchor);
        mergeSortHelper(points, nMid + 1, nRight, anchor);
        mergeArrays(points, nLeft, nMid, nRight, anchor);
    }
}

/* Merge function for Merge Sort */
/* Safer merge function with better error handling */
void mergeArrays(pointType points[], int nLeft, int nMid, int nRight, pointType anchor)
{
    static pointType leftArray[16384], rightArray[16384];
    int nLeftSize, nRightSize, i, j, k;

    nLeftSize = nMid - nLeft + 1;
    nRightSize = nRight - nMid;

    /* Enhanced bounds checking */
    if (nLeftSize <= 0 || nRightSize <= 0 || 
        nLeftSize > 16384 || nRightSize > 16384 ||
        nLeft < 0 || nRight >= 32768)
    {
        printf("Error: Invalid array bounds in merge operation\n");
        printf("Left size: %d, Right size: %d, Left: %d, Right: %d\n", 
               nLeftSize, nRightSize, nLeft, nRight);
        return;
    }

    /* Copy data to temporary arrays with bounds checking */
    for (i = 0; i < nLeftSize; i++)
    {
        if (nLeft + i < 32768) /* Ensure we don't exceed main array bounds */
        {
            leftArray[i] = points[nLeft + i];
        }
    }
    
    for (j = 0; j < nRightSize; j++)
    {
        if (nMid + 1 + j < 32768)
        {
            rightArray[j] = points[nMid + 1 + j];
        }
    }

    /* Rest of merge logic remains the same... */
    i = 0;
    j = 0;
    k = nLeft;

    while (i < nLeftSize && j < nRightSize && k <= nRight)
    {
        if (comparePointsByAngle(leftArray[i], rightArray[j], anchor) <= 0)
        {
            points[k] = leftArray[i];
            i++;
        }
        else
        {
            points[k] = rightArray[j];
            j++;
        }
        k++;
    }

    while (i < nLeftSize && k <= nRight)
    {
        points[k] = leftArray[i];
        i++;
        k++;
    }

    while (j < nRightSize && k <= nRight)
    {
        points[k] = rightArray[j];
        j++;
        k++;
    }
}