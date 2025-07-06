/**
 * @file stack.c
 * @brief Implementation of stack operations for convex hull computation
 * @author RANARA, Ramil Carlos, SIA, Justin Michael, TIU, Avram Nathaniel - Programmer
 * @date 7/6/2025
 * @version 1.0
 */

#include <stdio.h>
#include "stack.h"

/*
    Initializes an empty stack
    @param *s Pointer to a stack s
*/
void CREATE(Stack *s) {
    s->top = -1;
}

/*
    Determines if a stack has no elements
    @param *s Pointer to a stack s
    @return 1 if stack is empty, else 0
*/
int ISEMPTY(Stack *s) {
    return s->top < 0;
}

/*
    Determines if a stack has maximum number of elements
    @param *s Pointer to a stack s
    @return 1 if stack is full, else 0
*/
int ISFULL(Stack *s) {
    return s->top >= MAX - 1;
}

/*
    Returns the point at the secondmost top position of the stack
    @param *s Pointer to a stack s
    @return Secondmost top point in the stack
*/
Point NEXT_TO_TOP(Stack *s) {
    if (s->top > 0) {//runs if there are more than 2 points in the stack
        return s->arr[s->top-1];
    } else {//runs if there is one or no points in the stack
        printf("NEXT TO TOP ERROR: You are trying to access invalid index %ld\n", s->top-1);
        Point error;
        error.x = ERROR;
        error.y = ERROR;
        return error;
    }
}

/*
    Places an element on the topmost element of the stack
    @param *s Pointer to a stack s
    @param elem Point to be inserted in the stack
*/
void PUSH(Stack *s, Point elem) {
    if (!ISFULL(s)) {//runs if stack is not full
        s->arr[++(s->top)] = elem;
    } else {//runs if stack is full
        printf("PUSH ERROR: You are trying to access invalid index %ld\n", s->top+1);
    }
}

/*
    Removes the topmost element of the stack
    @param *s Pointer to a stack s
    @return Top point in stack
*/
Point POP(Stack *s) {
    if (!ISEMPTY(s)) {//runs if there is AT LEAST one point in the stack
        return s->arr[(s->top)--];
    } else {//runs if there are NO points in the stack
        printf("POP ERROR: You are trying to access invalid index %ld\n", s->top);
        Point error;
        error.x = ERROR;
        error.y = ERROR;
        return error;
    }
}

/*
    Returns the topmost element of the stack
    @param *s Pointer to a stack s
    @return Top point in stack
*/
Point TOP(Stack *s) {
    if (!ISEMPTY(s)) {//runs if there is AT LEAST one point in the stack
        return s->arr[s->top];
    } else {//runs if there are NO points in the stack
        printf("TOP ERROR: You are trying to access invalid index %ld\n", s->top);
        Point error;
        error.x = ERROR;
        error.y = ERROR;
        return error;
    }
}