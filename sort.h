#define _USE_MATH_DEFINES
#include <math.h>

/*
#ifndef HEADER_H
#define HEADER_H

#define MAX 32768

typedef struct{
    double x;
    double y;
    double angle;
}point;

typedef struct{
    int top;
    point array[MAX];
}stack;


void create(stack *S);
void push(stack *S, point elem);
point pop(stack *S);
point top(stack S);
point nextToTop(stack S);
int isFull(stack S);
int isEmpty(stack S);

#endif
*/

void merge(point references[], int left, int middle, int right);
void mergeSort(point references[], int left, int right);
void bubbleSort(point references[], int size);

int findAnchor(point set[], int n);
void findPolar(point anchor, point *reference);
int isCtrClockwise(point nextTop, point top, point current);