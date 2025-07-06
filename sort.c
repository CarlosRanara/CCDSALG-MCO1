/**
 * @file sort.c
 * @brief Implementation of sorting algorithms and geometric utilities
 * @author RANARA, Ramil Carlos, SIA, Justin Michael, TIU, Avram Nathaniel - Programmer
 * @date 7/6/2025 
 * @version 1.0
 */

#include "sort.h"

/* Purpose: Exchange the positions of two points in memory
   Returns: void
   @param first (Point*): Pointer to first point to swap
   @param second (Point*): Pointer to second point to swap
   Pre-condition:
   - Both pointers must point to valid Point structures
   Post-condition:
   - The two points have exchanged positions in memory */
void swap(Point *first, Point *second) {
    Point temp = *first;
    *first = *second;
    *second = temp;
}

/* Purpose: Determine the orientation of three ordered points using cross product
   Returns: -1 if counterclockwise turn, 1 if clockwise turn, 0 if collinear
   @param first (Point): First point (typically the anchor/reference point)
   @param second (Point): Second point (forms vector with first point)
   @param third (Point): Third point (forms vector with second point)
   Pre-condition:
   - All three points must have valid coordinates
   Post-condition:
   - Returns orientation based on cross product calculation */
int orientation(Point first, Point second, Point third) {
    double result = (second.x - first.x) * (third.y - second.y)
                    - (second.y - first.y) * (third.x - second.x);

    if (result > 0) {
        return -1;
    }

    else if (result < 0) {
        return 1;
    }

    return 0;
}

/* Purpose: Calculate squared Euclidean distance between two points
   Returns: Squared distance between the points (double)
   @param first (Point): First point
   @param second (Point): Second point
   Pre-condition:
   - Both points must have valid coordinates
   Post-condition:
   - Returns squared distance to avoid expensive sqrt() computation */
double distanceSquared(Point first, Point second) {
    double xResult = first.x - second.x;
    double yResult = first.y - second.y;

    return xResult*xResult + yResult*yResult;
}

/* Purpose: Find the anchor point and move it to index 0
   Returns: void
   @param points (Point[]): Array of points to process
   @param currentPoints (long int): Number of points in the array
   Pre-condition:
   - points array must contain at least 1 valid point
   - currentPoints must be > 0
   Post-condition:
   - The anchor point (bottommost-leftmost) is at index 0 */
void anchorToIndexZero(Point points[], long int currentPoints) {
    int minIndex = 0;
    for (long int i = 1; i < currentPoints; i++) {

        if (points[minIndex].y > points[i].y) {
            minIndex = i;
        }

        else if (points[minIndex].y == points[i].y) {

            if (points[minIndex].x > points[i].x) {
            minIndex = i;
            }

        }
    }

    swap(&points[0], &points[minIndex]);
}

/* Purpose: Sort points by polar angle relative to anchor using bubble sort
   Returns: void
   @param points (Point[]): Array of points to sort (index 0 must be anchor)
   @param currentPoints (long int): Total number of points in array
   @param anchor (Point): The reference point for angle calculations
   Pre-condition:
   - points[0] must be the anchor point
   - currentPoints must be >= 1
   - anchor should be points[0]
   Post-condition:
   - Points[1] to points[n-1] are sorted by increasing polar angle from anchor */
void bubbleSort(Point points[], long int currentPoints, Point anchor) {

    for (long int i = 1; i < currentPoints-1; i++) {
        for (long int j = 1; j < currentPoints-i; j++) {

            int outcome = orientation(anchor, points[j], points[j+1]);

            if (outcome == 1) {
                swap(&points[j], &points[j+1]);
            }

            else if (outcome == 0) {
                double jDiff = distanceSquared(anchor, points[j]);
                double jWith1Diff = distanceSquared(anchor, points[j+1]);

                if (jDiff > jWith1Diff) {
                    swap(&points[j], &points[j+1]);
                }
            }

        }
    }
}

/* Purpose: Merge two sorted subarrays by polar angle (helper for merge sort)
   Returns: void
   @param points (Point[]): Array containing both subarrays to merge
   @param start (long int): Starting index of first subarray
   @param middle (long int): Ending index of first subarray
   @param end (long int): Ending index of second subarray
   @param anchor (Point): Reference point for angle calculations
   Pre-condition:
   - Both subarrays [start,middle] and [middle+1,end] must be sorted by polar angle
   - start <= middle < end
   - All indices must be valid
   Post-condition:
   - The range [start, end] is merged and sorted by polar angle from anchor */
void merger(Point points[], long int start, long int middle, long int end, Point anchor) {
    long int i, j, k;
    long int leftEnd = middle - start + 1;
    long int rightEnd = end - middle;

    Point tempLeft[leftEnd], tempRight[rightEnd];

    for (i = 0; i < leftEnd; i++)
        tempLeft[i] = points[start + i];

    for (j = 0; j < rightEnd; j++)
        tempRight[j] = points[middle + 1 + j];

    i = 0;
    j = 0;
    k = start;

    while (i < leftEnd && j < rightEnd) {
        int result = orientation(anchor, tempLeft[i], tempRight[j]);

        if (result == -1) {
            points[k] = tempLeft[i];
            i++;
        }

        else if (result == 1) {
            points[k] = tempRight[j];
            j++;
        }

        else {
            double leftDiff = distanceSquared(anchor, tempLeft[i]);
            double rightDiff = distanceSquared(anchor, tempRight[j]);

            if (leftDiff > rightDiff) {
                points[k] = tempRight[j];
                j++;
            }
            else {
                points[k] = tempLeft[i];
                i++;
            }
        }

        k++;

    }

    while (i < leftEnd) {
        points[k] = tempLeft[i];
        i++;
        k++;
    }

    while (j < rightEnd) {
        points[k] = tempRight[j];
        j++;
        k++;
    }
}

/* Purpose: Sort points by polar angle relative to anchor using merge sort
   Returns: void
   @param points (Point[]): Array of points to sort
   @param start (long int): Starting index for sorting range
   @param end (long int): Ending index for sorting range
   Pre-condition:
   - points[0] must be the anchor point
   - start <= end
   - start and end must be valid indices
   Post-condition:
   - Points are sorted by increasing polar angle from points[0] (anchor) */
void mergeSort(Point points[], long int start, long int end) {
    if (start < end) {
        long int mid = start + (end - start) / 2;

        mergeSort(points, start, mid);
        mergeSort(points, mid + 1, end);

        merger(points, start, mid, end, points[0]);
    }
}