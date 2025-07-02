#include "graham_scan.h"

/*
    Performs Graham's Scan Algorithm using a Bubble sort algorithm to sort points
*/
void grahamScanSlow(point set[], stack *S, int n){
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
    printf("\nAnchor: %lf, %lf", anchor.x, anchor.y);

    //initialize reference points
    while(i < n - 1){
        if(j != index){
            references[i] = set[j];
            findPolar(anchor, &references[i]);
            printf("\nPolar angle of %lf, %lf: %lf", references[i].x, references[i].y, references[i].angle);
            i++;
        }
        j++;
    }

    //sort non-anchor/reference points
    bubbleSort(references, n - 1);
    printf("\nSorted points: ");
    for(i = 0; i < n - 1; i++){
        printf("\n%d). %.6lf, %.6lf ", (i + 1), references[i].x, references[i].y);
    }

    //perform Graham Scan
    i = 0;
    create(S);
    push(S, anchor);
    push(S, references[i]);
    i++;

    while(i < n - 1){
        if( isCtrClockwise(top(*S), references[i]) ){
            push(S, references[i]);
            printf("\npush!");
            i++;
        }
        else{
            printf("\npop!");
            pop(S);
        }
    
        printf("\t\t%d", i);
    }

    end = clock();

    printf("\nTime elapsed: %15lf", (double)(end - start));
}