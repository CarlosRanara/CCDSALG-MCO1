/* ============================================================================
 * FILE: sort.h
 * Sorting Algorithms Header
 * Programmer: [Your Name]
 * Tester: [Your Name]
 * ============================================================================ */
#ifndef SORT_H
#define SORT_H

#include "stack.h"

/* Sorting algorithms */
void bubbleSort(pointType points[], int nSize, pointType anchor);
void mergeSort(pointType points[], int nSize, pointType anchor);

/* Helper functions */
void mergeSortHelper(pointType points[], int nLeft, int nRight, pointType anchor);
void mergeArrays(pointType points[], int nLeft, int nMid, int nRight, pointType anchor);
int partitionPoints(pointType points[], int nLow, int nHigh, pointType anchor);
double computePolarAngle(pointType anchor, pointType point);
double computeDistanceSquared(pointType p1, pointType p2);
int comparePointsByAngle(pointType p1, pointType p2, pointType anchor);
void swapPoints(pointType *p1, pointType *p2);

#endif