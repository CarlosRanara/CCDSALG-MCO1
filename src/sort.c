/**
 * sort.c
 * Implementation of sorting algorithms for Graham's Scan
 * Group 16 Assignment: Bubble Sort (slow) + Merge Sort (fast)
 * CCDSALG Term 3, AY 2024-2025
 */

#include "sort.h"

#define EPSILON 0.000000001

void findAnchorPoint(Point points[], int n, int *anchorIndex) {
    int i;
    int minIdx;
    
    minIdx = 0;
    i = 1;
    
    while (i < n) {
        /* Pick the bottom-most or left-most point in case of tie */
        if ((points[i].y < points[minIdx].y) ||
            (points[i].y == points[minIdx].y && points[i].x < points[minIdx].x)) {
            minIdx = i;
        }
        i++;
    }
    
    *anchorIndex = minIdx;
}

void calculateDistanceSquared(Point p1, Point p2, double *result) {
    double dx;
    double dy;
    
    dx = p1.x - p2.x;
    dy = p1.y - p2.y;
    
    *result = dx * dx + dy * dy;
}

void calculateOrientation(Point p, Point q, Point r, int *orientResult) {
    double val;
    int bCollinear;
    
    val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);
    
    areDoublesEqual(val, 0.0, &bCollinear);
    
    if (bCollinear) {
        *orientResult = 0;  /* collinear */
    } else if (val > 0) {
        *orientResult = 1;  /* clockwise */
    } else {
        *orientResult = 2;  /* counterclockwise */
    }
}

void comparePointsByPolarAngle(Point p1, Point p2, Point anchor, int *compareResult) {
    int nOrient;
    double dDist1;
    double dDist2;
    int nDistCompare;
    
    /* Find orientation */
    calculateOrientation(anchor, p1, p2, &nOrient);
    
    if (nOrient == 0) {
        /* If points are collinear, sort by distance from anchor */
        calculateDistanceSquared(anchor, p1, &dDist1);
        calculateDistanceSquared(anchor, p2, &dDist2);
        
        nDistCompare = 0;
        if (dDist1 <= dDist2) {
            nDistCompare = -1;
        } else {
            nDistCompare = 1;
        }
        
        *compareResult = nDistCompare;
    } else {
        /* If we have a counterclockwise orientation, p1 comes first */
        if (nOrient == 2) {
            *compareResult = -1;
        } else {
            *compareResult = 1;
        }
    }
}

void swapPoints(Point *a, Point *b) {
    Point temp;
    
    temp = *a;
    *a = *b;
    *b = temp;
}

/* SLOW SORTING ALGORITHM: Bubble Sort (Group 16) */
void bubbleSortPoints(Point points[], int n, int anchorIndex) {
    int i;
    int j;
    int nCompareResult;
    Point anchor;
    
    /* Swap anchor to first position */
    swapPoints(&points[0], &points[anchorIndex]);
    
    anchor = points[0];
    
    /* Sort remaining points by polar angle with respect to anchor */
    i = 1;
    while (i < n - 1) {
        j = 1;
        while (j < n - i) {
            comparePointsByPolarAngle(points[j], points[j + 1], anchor, &nCompareResult);
            
            if (nCompareResult > 0) {
                swapPoints(&points[j], &points[j + 1]);
            }
            j++;
        }
        i++;
    }
}

/* FAST SORTING ALGORITHM: Merge Sort (Group 16) */
void mergeSortPoints(Point points[], int n, int anchorIndex) {
    Point anchor;
    Point temp[MAX_STACK_SIZE];
    
    /* Swap anchor to first position */
    swapPoints(&points[0], &points[anchorIndex]);
    
    anchor = points[0];
    
    /* Sort remaining points using merge sort */
    if (n > 1) {
        mergeSortPointsUtil(points, temp, 1, n - 1, anchor);
    }
}

void mergeSortPointsUtil(Point points[], Point temp[], int low, int high, Point anchor) {
    int mid;
    
    if (low < high) {
        mid = low + (high - low) / 2;
        
        mergeSortPointsUtil(points, temp, low, mid, anchor);
        mergeSortPointsUtil(points, temp, mid + 1, high, anchor);
        mergePoints(points, temp, low, mid, high, anchor);
    }
}

void mergePoints(Point points[], Point temp[], int low, int mid, int high, Point anchor) {
    int i;
    int j;
    int k;
    int nCompareResult;
    
    /* Copy data to temp arrays */
    i = low;
    while (i <= high) {
        temp[i] = points[i];
        i++;
    }
    
    /* Merge the temp arrays back into points[low..high] */
    i = low;      /* Initial index of left subarray */
    j = mid + 1;  /* Initial index of right subarray */
    k = low;      /* Initial index of merged subarray */
    
    while (i <= mid && j <= high) {
        comparePointsByPolarAngle(temp[i], temp[j], anchor, &nCompareResult);
        
        if (nCompareResult <= 0) {
            points[k] = temp[i];
            i++;
        } else {
            points[k] = temp[j];
            j++;
        }
        k++;
    }
    
    /* Copy the remaining elements of left subarray, if any */
    while (i <= mid) {
        points[k] = temp[i];
        i++;
        k++;
    }
    
    /* Copy the remaining elements of right subarray, if any */
    while (j <= high) {
        points[k] = temp[j];
        j++;
        k++;
    }
}

void areDoublesEqual(double a, double b, int *result) {
    double diff;
    
    diff = a - b;
    if (diff < 0) {
        diff = -diff;
    }
    
    *result = (diff < EPSILON);
}