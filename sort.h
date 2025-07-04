#ifndef SORT
#define SORT

    #include "stack.h"

    /*
        Prototypes for Sorting Algorithms
    */
    void anchorToIndexZero(Point points[], long int currentPoints);
    void bubbleSort(Point points[], long int currentPoints, Point anchor);
    int orientation(Point first, Point second, Point third);
    void swap(Point *first, Point *second);
    double distanceSquared(Point first, Point second);
    void mergeSort(Point points[], long int start, long int end);
    void merger(Point points[], long int start, long int middle, long int end, Point anchor);

#endif