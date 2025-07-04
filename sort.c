/* ============================================================================
 * FILE: sort.c
 * Sorting Algorithms Implementation
 * Programmer: [Your Name]
 * Tester: [Your Name]
 * ============================================================================ */
#include "sort.h"
#include <stdio.h>

/* Computes polar angle from anchor to point without using math.h */
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

    /* Use cross product approach for better accuracy */
    /* We'll use the slope dy/dx but handle quadrants properly */
    if (dDx == 0.0)
    {
        if (dDy > 0.0)
        {
            return 1.5707963268; /* PI/2 */
        }
        else
        {
            return -1.5707963268; /* -PI/2 */
        }
    }

    if (dDy == 0.0)
    {
        if (dDx > 0.0)
        {
            return 0.0; /* 0 degrees */
        }
        else
        {
            return 3.1415926536; /* PI */
        }
    }

    /* For simplicity, use a comparison based on slopes and quadrants */
    /* This avoids complex atan approximations */
    if (dDx > 0.0 && dDy > 0.0)
    {
        /* First quadrant: return small positive value based on slope */
        return dDy / dDx;
    }
    else if (dDx < 0.0 && dDy > 0.0)
    {
        /* Second quadrant: return PI - slope */
        return 3.1415926536 + dDy / dDx;
    }
    else if (dDx < 0.0 && dDy < 0.0)
    {
        /* Third quadrant: return PI + slope */
        return 3.1415926536 - dDy / dDx;
    }
    else
    {
        /* Fourth quadrant: return 2*PI - slope */
        return 6.2831853072 + dDy / dDx;
    }
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
void mergeArrays(pointType points[], int nLeft, int nMid, int nRight, pointType anchor)
{
    static pointType leftArray[16384], rightArray[16384];
    int nLeftSize, nRightSize, i, j, k;

    nLeftSize = nMid - nLeft + 1;
    nRightSize = nRight - nMid;

    /* Check array bounds to prevent overflow */
    if (nLeftSize > 16384 || nRightSize > 16384)
    {
        printf("Error: Array size too large for merge operation\n");
        return;
    }

    /* Copy data to temporary arrays */
    for (i = 0; i < nLeftSize; i++)
    {
        leftArray[i] = points[nLeft + i];
    }
    for (j = 0; j < nRightSize; j++)
    {
        rightArray[j] = points[nMid + 1 + j];
    }

    /* Merge the temporary arrays back into points[nLeft..nRight] */
    i = 0;
    j = 0;
    k = nLeft;

    while (i < nLeftSize && j < nRightSize)
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

    /* Copy remaining elements of leftArray[], if any */
    while (i < nLeftSize)
    {
        points[k] = leftArray[i];
        i++;
        k++;
    }

    /* Copy remaining elements of rightArray[], if any */
    while (j < nRightSize)
    {
        points[k] = rightArray[j];
        j++;
        k++;
    }
}