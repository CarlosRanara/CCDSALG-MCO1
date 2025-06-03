/**
 * graham_scan.h
 * Implementation of Graham's Scan algorithm
 * Group 16 Assignment: Bubble Sort (slow) + Merge Sort (fast)
 * CCDSALG Term 3, AY 2024-2025
 */

#ifndef GRAHAM_SCAN_H
#define GRAHAM_SCAN_H

#include "stack.h"
#include "sort.h"
#include <time.h>

/**
 * Graham's Scan implementation using bubble sort (slow version - Group 16)
 * @param points Array of input points
 * @param n Number of input points
 * @param hull Array to store the convex hull points
 * @param hullSize Pointer to store the number of points in the convex hull
 */
void grahamScanSlow(Point points[], int n, Point hull[], int *hullSize);

/**
 * Graham's Scan implementation using merge sort (fast version - Group 16)
 * @param points Array of input points
 * @param n Number of input points
 * @param hull Array to store the convex hull points
 * @param hullSize Pointer to store the number of points in the convex hull
 */
void grahamScanFast(Point points[], int n, Point hull[], int *hullSize);

#endif /* GRAHAM_SCAN_H */