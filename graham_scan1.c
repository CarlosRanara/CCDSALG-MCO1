#include "graham_scan.h"
#include "stack.h"
#include "sort.h"

void initialPush(Stack *hull, Point points[]) {
    PUSH(hull, points[0]);
    PUSH(hull, points[1]);
    PUSH(hull, points[2]);
}

double calculateTime(clock_t start, clock_t end) {
    return (double)(end - start);
}

void bubbleGraham(Stack *hull, Point points[], long int currentPoints) {
    clock_t start, end;
    double duration;
    
    start = clock();
    anchorToIndexZero(points, currentPoints);
    bubbleSort(points, currentPoints, points[0]);

    initialPush(hull, points);

    for (long int i = 3; i < currentPoints; i++) {

        while (orientation(NEXT_TO_TOP(hull), TOP(hull), points[i]) != -1) {
            POP(hull);
        }

        PUSH(hull, points[i]);
    }

    end = clock();
    duration = calculateTime(start, end);

    printf("Bubble Graham:\nInput Size: %6ld\nElapsed Time: %15lf\n", currentPoints, duration);
}