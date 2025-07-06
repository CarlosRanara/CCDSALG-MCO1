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
    Purpose: Initializes an empty stack
    Returns: void
    @param *s Pointer to a stack s
    Pre-condition:
    - None
    Post-condition:
    - Stack s is initialized
*/
void CREATE(Stack *s) {
    s->top = -1;
}

/*
    Purpose: Determines if a stack has no elements
    Returns: 1 if stack is empty, 0 if not empty
    @param *s Pointer to a stack s
    Pre-condition:
    - None
    Post-condition:
    - Returns evaluation of emptiness of the stack
*/
int ISEMPTY(Stack *s) {
    return s->top < 0;
}

/*
    Purpose: Determines if a stack has maximum number of elements
    Returns: 1 if stack is full, 0 if not full
    @param *s Pointer to a stack s
    Pre-condition:
    - None
    Post-condition:
    - Returns evaluation of fullness of the stack
*/
int ISFULL(Stack *s) {
    return s->top >= MAX - 1;
}

/*
    Purpose: Checks if there are 2 or more points in the stack 
             and gives the point at the secondmost top position of the stack
    Returns: If there are 2 or more points, return secondmost top point in the stack
             if there are less than 2 points, returns a point with -999 x and y coordinate values
    @param *s Pointer to a stack s
    Pre-condition:
    - None
    Post-condition:
    - Returns the secondmost top point in the stack
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
    Purpose: Checks if a stack is full and places an element
             on the topmost element of the stack
    Returns: void
    @param *s Pointer to a stack s
    @param elem Point to be inserted in the stack
    Pre-condition:
    - None
    Post-condition:
    - New point is added to top of the stack
*/
void PUSH(Stack *s, Point elem) {
    if (!ISFULL(s)) {//runs if stack is not full
        s->arr[++(s->top)] = elem;
    } else {//runs if stack is full
        printf("PUSH ERROR: You are trying to access invalid index %ld\n", s->top+1);
    }
}

/*
    Purpose: Checks if a stack is empty and removes the topmost element of the stack
    Returns: If there is at least one point in the stack, returns top point
             if there are less than 2 points, returns a point with -999 x and y coordinate values
    @param *s Pointer to a stack s
    Pre-condition:
    - None
    Post-condition:
    - Top point is removed from the stack and returned
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
    Purpose: Checks if a stack is empty and gives the topmost element of the stack
    Returns: If there is at least one point in the stack, returns top point
             if there are less than 2 points, returns a point with -999 x and y coordinate values
    @param *s Pointer to a stack s
    Pre-condition:
    - None
    Post-condition:
    - Top point is returned
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