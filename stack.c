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
    if(isFull(S))
        printf("\nStack at full capacity! Cannot push element");
    else{
        //printf("\nPushed %lf, %lf to index %d", elem.x, elem.y, S->top);
        S->array[S->top] = elem;
        S->top++;
    }
}

/*
    This removes the top element of the stack and returns it
*/
point pop(stack *S){
    point tempPoint;

    if(isEmpty(S)){
        printf("\nStack is empty! Cannot pop any element");
        tempPoint.x = -888;
        tempPoint.y = -888;
    }
    else{
        //printf("\npopping %lf, %lf", top(S).x, top(S).y);
        tempPoint = top(S);
        S->top--;
    }

    return tempPoint;
}

/*
    This returns the top element of the stack
*/
point top(stack *S){
    if(isEmpty(S)){
        point null;
        null.x = -888;
        null.y = -888;
        return null;
    }
    else
        return S->array[S->top - 1];
}

/*
    This returns the secondmost top element of the stack
*/
point nextToTop(stack *S){
    if(S->top <= 1){
        point null;
        null.x = -888;
        null.y = -888;
        return null;
    }
    else
        return S->array[S->top - 2];
}

/*
    This determines if the stack has reached the maximum number of elements
    Returns 1 if TRUE, 0 if FALSE
*/
int isFull(stack *S){
    return S->top == MAX;
}

/*
    This determines if the stack has no elements in it
    Returns 1 if TRUE, 0 if FALSE
*/
int isEmpty(stack *S){
    return S->top == 0;
}
