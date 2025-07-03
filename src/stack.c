/**
 * stack.c
 * Implementation of the stack data structure for Graham's Scan algorithm
 * Group 16 - CCDSALG Term 3, AY 2024-2025
 *
 * Programmers: 
 * RANARA, Ramil Carlos
 * SIA, Justin Michael
 * TIU, Avram Nathaniel
 *
 * Code Testers:
 * RANARA, Ramil Carlos
 * SIA, Justin Michael
 * TIU, Avram Nathaniel
* 
 * This module implements an array-based stack data structure specifically
 * designed for the Graham's Scan convex hull algorithm. The stack can hold
 * up to 32,768 Point elements and includes a special NEXT-TO-TOP operation
 * required by the Graham's Scan algorithm.
 */

#include "stack.h"

void createStack(Stack *s) {
    /* Initialize the stack by setting top to -1 (empty stack indicator) */
    s->top = -1;
}

void pushToStack(Stack *s, Point elem, int *bSuccess) {
    int bFull;
    
    *bSuccess = 0;
    bFull = isStackFull(s);
    
    if (!bFull) {
        /* Increment top index and add the element */
        s->top++;
        s->items[s->top] = elem;
        *bSuccess = 1;
    } else {
        fprintf(stderr, "Stack overflow: Cannot push element\n");
    }
}

void popFromStack(Stack *s, Point *elem, int *bSuccess) {
    int bEmpty;
    
    *bSuccess = 0;
    bEmpty = isStackEmpty(s);
    
    if (!bEmpty) {
        /* Get the top element and decrement the top index */
        *elem = s->items[s->top];
        s->top--;
        *bSuccess = 1;
    } else {
        fprintf(stderr, "Stack underflow: Cannot pop from empty stack\n");
    }
}

void getTopOfStack(Stack *s, Point *elem, int *bSuccess) {
    int bEmpty;
    
    *bSuccess = 0;
    bEmpty = isStackEmpty(s);
    
    if (!bEmpty) {
        /* Return the top element without removing it */
        *elem = s->items[s->top];
        *bSuccess = 1;
    } else {
        fprintf(stderr, "Stack is empty: Cannot get top element\n");
    }
}

void getNextToTopOfStack(Stack *s, Point *elem, int *bSuccess) {
    *bSuccess = 0;
    
    if (s->top >= 1) {
        /* Return the element below the top (essential for Graham's Scan) */
        *elem = s->items[s->top - 1];
        *bSuccess = 1;
    } else {
        fprintf(stderr, "Stack has less than two elements: Cannot get next-to-top\n");
    }
}

int isStackFull(Stack *s) {
    int bFull;
    
    /* Stack is full when top index reaches maximum capacity - 1 */
    bFull = (s->top == MAX_STACK_SIZE - 1);
    
    return bFull;
}

int isStackEmpty(Stack *s) {
    int bEmpty;
    
    /* Stack is empty when top index is -1 */
    bEmpty = (s->top == -1);
    
    return bEmpty;
}

int getStackSize(Stack *s) {
    int nSize;
    
    /* Size is top index + 1 (since top starts at -1 for empty stack) */
    nSize = s->top + 1;
    
    return nSize;
}
