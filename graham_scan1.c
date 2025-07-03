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
    bubbleSort(references, n - 1);

    //perform Graham Scan
    i = 0;
    push(S, anchor);
    push(S, references[i]);
    i++;

    while(i < n - 1){
        if(S->top > 1 && !isCtrClockwise(nextToTop(S), top(S), references[i])){
            pop(S);
        // Don't increment i - check same point again with new stack top
        }
        else{
            push(S, references[i]);
            i++;  // Only increment when we successfully push
        }
    }


    end = clock();

    printf("\nTime elapsed: %15lf seconds", (double)(end - start));
}