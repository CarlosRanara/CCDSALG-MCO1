/**
 * sort.h
 * Sorting algorithm implementations for Graham's Scan algorithm
 */

#ifndef SORT_H
#define SORT_H

#include "stack.h"

/**
 * Find the anchor point (point with lowest y-coordinate)
 * If multiple points have the same y-coordinate, choose the one with the lowest x-coordinate
 * @param points Array of points
 * @param n Number of points
 * @param anchorIndex Pointer to store the anchor point index
 */
void findAnchorPoint(Point points[], int n, int *anchorIndex);

/**
 * Calculate the squared distance between two points
 * @param p1 First point
 * @param p2 Second point
 * @param result Pointer to store the result
 */
void calculateDistanceSquared(Point p1, Point p2, double *result);

/**
 * Calculate the orientation of triplet (p, q, r)
 * @param p First point
 * @param q Second point
 * @param r Third point
 * @param orientResult Pointer to store the result:
 *        0 --> p, q and r are collinear
 *        1 --> Clockwise
 *        2 --> Counterclockwise
 */
void calculateOrientation(Point p, Point q, Point r, int *orientResult);

/**
 * Compare two points based on polar angle with respect to anchor
 * @param p1 First point
 * @param p2 Second point
 * @param anchor Anchor point
 * @param compareResult Pointer to store the result:
 *        -1 if p1 comes before p2
 *         0 if p1 and p2 are equal
 *         1 if p1 comes after p2
 */
void comparePointsByPolarAngle(Point p1, Point p2, Point anchor, int *compareResult);

/**
 * Sort points based on polar angle with respect to the anchor point
 * For points with same angle, keep the closest one first
 * @param points Array of points
 * @param n Number of points
 * @param anchorIndex Index of the anchor point
 */
void bubbleSortPoints(Point points[], int n, int anchorIndex);

/**
 * Quick sort implementation for sorting points based on polar angle
 * @param points Array of points
 * @param n Number of points
 * @param anchorIndex Index of the anchor point
 */
void quickSortPoints(Point points[], int n, int anchorIndex);

/**
 * Helper function for quickSort
 * @param points Array of points
 * @param low Starting index
 * @param high Ending index
 * @param anchor The anchor point
 */
void quickSortPointsUtil(Point points[], int low, int high, Point anchor);

/**
 * Partition function for quickSort
 * @param points Array of points
 * @param low Starting index
 * @param high Ending index
 * @param anchor The anchor point
 * @param partitionIndex Pointer to store the partition index
 */
void partitionPoints(Point points[], int low, int high, Point anchor, int *partitionIndex);

/**
 * Swap two points
 * @param a First point
 * @param b Second point
 */
void swapPoints(Point *a, Point *b);

/**
 * Check if two doubles are approximately equal
 * @param a First value
 * @param b Second value
 * @param result Pointer to store the result (1 if equal, 0 otherwise)
 */
void areDoublesEqual(double a, double b, int *result);

#endif /* SORT_H */