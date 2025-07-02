#include "stack.h"

/*
    This initializes a Stack called S
*/
void create(stack *S){
    S->top = 0;
}

/*
    This inserts an element at the top of the stack
*/
void push(stack *S, point elem){
    S->array[S->top] = elem;
    S->top++;
}

/*
    This removes the top element of the stack and returns it
*/
point pop(stack *S){
    point tempPoint;

    tempPoint = top(*S);
    S->top--;
    return tempPoint;
}

/*
    This returns the top element of the stack
*/
point top(stack S){
    return S.array[S.top - 1];
}

/*
    This returns the secondmost top element of the stack
*/
point nextToTop(stack S){
    return S.array[S.top - 2];
}

/*
    This determines if the stack has reached the maximum number of elements
    Returns 1 if TRUE, 0 if FALSE
*/
int isFull(stack S){
    if(S.top == MAX)
        return 1;//true
    else
        return 0;//false
}

/*
    This determines if the stack has no elements in it
    Returns 1 if TRUE, 0 if FALSE
*/
int isEmpty(stack S){
    if(S.top == 0)
        return 1;//true
    else    
        return 0;//false
}
