#ifndef SORT
#define SORT

    #include "stack.h"

    /*
        Prototypes for Sorting Algorithms
    */
    void anchorToIndexZero(Point points[], int currentPoints);
    void bubbleSort(Point points[], int currentPoints, Point anchor);
    int orientation(Point anchor, Point first, Point second);
    void swap(Point *first, Point *second);
    double distanceSquared(Point first, Point second);
    void mergeSort(Point points[], int start, int end);
    void merger(Point points[], int start, int middle, int end, Point anchor);

#endif