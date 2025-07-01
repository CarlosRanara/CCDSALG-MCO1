#ifndef MANGO_GRAHAM
#define MANGO_GRAHAM

    #include "sort.h"
    #include "stack.h"
    #include <time.h>

    /*
        Function prototypes
    */
    void bubbleGraham(Stack *hull, Point points[], long int currentPoints);
    void mergeGraham(Stack *hull, Point points[], long int currentPoints);
    void initialPush(Stack *hull, Point points[]);
    double calculateTime(clock_t start, clock_t end);

#endif