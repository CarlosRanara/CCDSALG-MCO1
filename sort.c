#include "sort.h"

void swap(Point *first, Point *second) {
    Point temp = *first;
    *first = *second;
    *second = temp;
}

int orientation(Point anchor, Point first, Point second) {
    double result = (first.x - anchor.x) * (second.y - anchor.y)
                    - (second.x - anchor.x) * (first.y - anchor.y);

    if (result > 0) {
        return -1;
    }

    else if (result < 0) {
        return 1;
    }

    return 0;
}

double distanceSquared(Point first, Point second) {
    double xResult = first.x - second.x;
    double yResult = first.y - second.y;

    return xResult*xResult + yResult*yResult;
}

void anchorToIndexZero(Point points[], int currentPoints) {
    int minIndex = 0;
    for (int i = 1; i < currentPoints; i++) {

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

void bubbleSort(Point points[], int currentPoints, Point anchor) {

    for (int i = 1; i < currentPoints-1; i++) {
        for (int j = 1; j < currentPoints-i; j++) {

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

void merger(Point points[], int start, int middle, int end, Point anchor) {
    int i, j, k;
    int leftEnd = middle - start + 1;
    int rightEnd = end - middle;

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

void mergeSort(Point points[], int start, int end) {
    if (start < end) {
        int mid = start + (end - start) / 2;

        mergeSort(points, start, mid);
        mergeSort(points, mid + 1, end);

        merger(points, start, mid, end, points[0]);
    }
}