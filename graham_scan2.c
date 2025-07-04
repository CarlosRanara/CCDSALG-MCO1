#include "graham_scan.h"
#include "stack.h"
#include "sort.h"

int checkPoints(long int currentPoints) {
    if (currentPoints >= 3) {
        return 1;
    }

    return 0;
}

void initialPush(Stack *hull, Point points[]) {
    PUSH(hull, points[0]);
    PUSH(hull, points[1]);
    PUSH(hull, points[2]);
}

double calculateTime(clock_t start, clock_t end) {
    return (double)(end - start);
}

void mergeGraham(Stack *hull, Point points[], long int currentPoints) {
    if (checkPoints(currentPoints)) {

        clock_t start, end;
        double duration;

        start = clock();
        anchorToIndexZero(points, currentPoints);
        mergeSort(points, 0, currentPoints);

        initialPush(hull, points);

        for (long int i = 3; i < currentPoints; i++) {

            while (hull->top >= 1 && orientation(NEXT_TO_TOP(hull), TOP(hull), points[i]) != -1) {
                POP(hull);
            }

            PUSH(hull, points[i]);
        }

        end = clock();
        duration = calculateTime(start, end);

        printf("Mergesort Graham:\nInput Size: %6ld\nElapsed Time: %15lf\n", currentPoints, duration);
        
    }
}