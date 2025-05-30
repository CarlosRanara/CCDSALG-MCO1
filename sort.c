/**
 * sort.c
 * Implementation of sorting algorithms for Graham's Scan
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

/* SLOW SORTING ALGORITHM: Bubble Sort */
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

/* FAST SORTING ALGORITHM: Quick Sort */
void quickSortPoints(Point points[], int n, int anchorIndex) {
    Point anchor;
    
    /* Swap anchor to first position */
    swapPoints(&points[0], &points[anchorIndex]);
    
    anchor = points[0];
    
    /* Sort remaining points using quick sort */
    if (n > 1) {
        quickSortPointsUtil(points, 1, n - 1, anchor);
    }
}

void quickSortPointsUtil(Point points[], int low, int high, Point anchor) {
    int pi;
    
    if (low < high) {
        partitionPoints(points, low, high, anchor, &pi);
        
        quickSortPointsUtil(points, low, pi - 1, anchor);
        quickSortPointsUtil(points, pi + 1, high, anchor);
    }
}

void partitionPoints(Point points[], int low, int high, Point anchor, int *partitionIndex) {
    Point pivot;
    int i;
    int j;
    int nCompareResult;
    
    pivot = points[high];
    i = (low - 1);
    
    j = low;
    while (j <= high - 1) {
        comparePointsByPolarAngle(points[j], pivot, anchor, &nCompareResult);
        
        if (nCompareResult < 0) {
            i++;
            swapPoints(&points[i], &points[j]);
        }
        j++;
    }
    
    swapPoints(&points[i + 1], &points[high]);
    *partitionIndex = (i + 1);
}

void areDoublesEqual(double a, double b, int *result) {
    double diff;
    
    diff = a - b;
    if (diff < 0) {
        diff = -diff;
    }
    
    *result = (diff < EPSILON);
}