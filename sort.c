#include "sort.h"
#define _USE_MATH_DEFINES
#include <math.h>

/*
    This is used in the function mergeSort().
    It's recursively called to combine two arrays
*/
void merge(point references[], int left, int middle, int right){
    int l, r, k;
    int limitOne = middle - left + 1, limitTwo = right - middle;
    point arrayLeft[limitOne];
    point arrayRight[limitTwo];

    //make the two temporary arrays
    for(l = 0; l < limitOne; l++){
        arrayLeft[l] = references[left + l];
    }
    for(r = 0; r < limitTwo; r++){
        arrayRight[r] = references[middle + r + 1];
    }

    //reset counters
    l = 0;
    r = 0;
    k = left;

    //do comparisons
    while(l < limitOne && r < limitTwo){
        if(arrayLeft[l].angle < arrayRight[r].angle){
            references[k] = arrayLeft[l];
            l++;
            k++;
        }
        else{
            references[k] = arrayRight[r];
            r++;
            k++;
        }
    }

    //add any leftover variables
    while(l < limitOne){
        references[k] = arrayLeft[l];
        l++;
        k++;
    }

    while(r < limitTwo){
        references[k] = arrayRight[r];
        r++;
        k++;
    }
}

/*
    This sorts an array of points in increasing order using
    the merge sort algorithm with time complexity O(n * log n)
*/
void mergeSort(point references[], int left, int right){
    if(left < right){//if there is more than one element
        int middle;

        //get middle point thru midpoint formula
        middle = (left + right) / 2;

        //break down array into two halves
        mergeSort(references, left, middle);
        mergeSort(references, middle + 1, right);
        merge(references, left, middle, right);
    }

}

/*
    This sorts an array of doubles in increasing order
    using the bubble sort algorithm with time complexity O(n^2)
*/
void bubbleSort(point references[], int size){
    int i, j;
    point tempPoint;
    for(i  = 0; i < size - 1; i++){
        for(j = 0; j < size - i - 1; j++){
            if(references[j].angle > references[j + 1].angle){
                //printf("\nSwapping %lf with %lf", references[j].angle, references[j + 1].angle);
                tempPoint = references[j];
                references[j] = references[j + 1];
                references[j + 1] = tempPoint;
            }
        }
    }
}

/*
    Finds the Anchor point given a set of points
*/
int findAnchor(point set[], int n){
    int i, min = 0;

    for(i = 0; i < n; i++){
        //if y-coordinate at index min is greater than
        //y-coordinate at index i, i the is new anchor(min)
        if(set[min].y > set[i].y)
            min = i;

        //if y-coordinate at index min is equal to y-coordinate at index i
        //and x-coordinate at index min is greater than x-coordinate at index i,
        //i is the new anchor(min)
        else if(set[min].y == set[i].y && set[min].x > set[i].x)
            min = i;
    }

    return min;//return index of anchor point
}

/*
    Finds the Polar angle of a reference point with respect to the anchor point
*/
void findPolar(point anchor, point *reference){
    double distanceX;
    double distanceY;

    //get the horizontal and vertical distance
    distanceX = reference->x - anchor.x;
    distanceY = reference->y - anchor.y;

    //computing polar angle by formula: arctan(y / x)
    //atan (or arctan) requires an angle in radians so multiply by pi/180
    //atan gives an angle in radians so multiply by 180/pi to get degrees 
    reference->angle = (atan((distanceY / distanceX))) * (180.0 / M_PI);
}



/*
    Determines if the angle made from the starting point to the end point is counter-clockwise or not.
    Returns 1 if counter-clockwise, 0 if clockwise.
*/
int isCtrClockwise(point start, point end){
    double vectorS, vectorE;

    vectorS = sqrt( pow(start.x, 2) + pow(start.y, 2));
    vectorE = sqrt( pow(end.x, 2) + pow(end.y, 2));

    if(vectorS * vectorE > 0)
        return 1;
    else
        return 0;
}