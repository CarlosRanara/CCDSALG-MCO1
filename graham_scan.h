/**
 * graham_scan.h
 * Implementation of Graham's Scan algorithm
 */

#ifndef GRAHAM_SCAN_H
#define GRAHAM_SCAN_H

#include "stack.h"
#include "sort.h"
#include <time.h>

/**
 * Graham's Scan implementation using bubble sort (slow version)
 * @param points Array of input points
 * @param n Number of input points
 * @param hull Array to store the convex hull points
 * @param hullSize Pointer to store the number of points in the convex hull
 */
void grahamScanSlow(Point points[], int n, Point hull[], int *hullSize);

/**
 * Graham's Scan implementation using quick sort (fast version)
 * @param points Array of input points
 * @param n Number of input points
 * @param hull Array to store the convex hull points
 * @param hullSize Pointer to store the number of points in the convex hull
 */
void grahamScanFast(Point points[], int n, Point hull[], int *hullSize);

#endif /* GRAHAM_SCAN_H */