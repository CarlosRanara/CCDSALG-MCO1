#include "graham_scan.h"

/*
    Performs Graham's Scan Algorithm using a Merge sort algorithm to sort points
*/
void grahamScanFast(point set[], stack *S, int n){
    int i = 0, j = 0;
    int index;
    clock_t start, end;
    point anchor;
    point references[n - 1];

    //start timer
    start = clock();

    //initialize anchor point
    index = findAnchor(set, n);
    anchor = set[index];

    //initialize reference points
    while(i < n - 1){
        if(j != index){
            references[i] = set[j];
            findPolar(anchor, &references[i]);
            i++;
        }
        j++;
    }

    //sort non-anchor/reference points
    mergeSort(references, 0, n - 2);

    //perform Graham Scan
    i = 0;
    create(S);
    push(S, anchor);
    push(S, references[i]);
    i++;
    while(i < n - 1){
        if( isCtrClockwise(references[i - 1], references[i]) ){
            push(S, references[i]);
            i++;
        }
        else{
            pop(S);
        }
    }

    end = clock();

    printf("\nTime elapsed: %15lf", (double)(end - start));
}