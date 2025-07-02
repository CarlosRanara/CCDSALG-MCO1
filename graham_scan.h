#include "stack.c"
#include "sort.c"
#include <math.h>
#include <time.h>

void grahamScanSlow(point set[], stack *S, int n);
void grahamScanFast(point set[], stack *S, int n);