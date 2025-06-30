#include <stdio.h>
#include <stdlib.h>

#define MAX 32768

typedef struct{
    int top;
    double array[MAX];
}stack;

void create(stack *S);
void push(stack *S, double elem);
double pop(stack *S);
double top(stack S);
double nextToTop(S);
int isFull(stack S);
int isEmpty(stack S);