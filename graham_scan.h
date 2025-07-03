
#include <time.h>

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

void grahamScanSlow(point set[], stack *S, int n);
void grahamScanFast(point set[], stack *S, int n);