/**
 * stack.c
 * Implementation of the stack data structure for Graham's Scan algorithm
 */

#include "stack.h"

void createStack(Stack *s) {
    s->top = -1;
}

void pushToStack(Stack *s, Point elem, int *bSuccess) {
    int bFull;
    
    *bSuccess = 0;
    bFull = isStackFull(s);
    
    if (!bFull) {
        s->top++;
        s->items[s->top] = elem;
        *bSuccess = 1;
    } else {
        fprintf(stderr, "Stack overflow\n");
    }
}

void popFromStack(Stack *s, Point *elem, int *bSuccess) {
    int bEmpty;
    
    *bSuccess = 0;
    bEmpty = isStackEmpty(s);
    
    if (!bEmpty) {
        *elem = s->items[s->top];
        s->top--;
        *bSuccess = 1;
    } else {
        fprintf(stderr, "Stack underflow\n");
    }
}

void getTopOfStack(Stack *s, Point *elem, int *bSuccess) {
    int bEmpty;
    
    *bSuccess = 0;
    bEmpty = isStackEmpty(s);
    
    if (!bEmpty) {
        *elem = s->items[s->top];
        *bSuccess = 1;
    } else {
        fprintf(stderr, "Stack is empty\n");
    }
}

void getNextToTopOfStack(Stack *s, Point *elem, int *bSuccess) {
    *bSuccess = 0;
    
    if (s->top >= 1) {
        *elem = s->items[s->top - 1];
        *bSuccess = 1;
    } else {
        fprintf(stderr, "Stack has less than two elements\n");
    }
}

int isStackFull(Stack *s) {
    int bFull;
    
    bFull = (s->top == MAX_STACK_SIZE - 1);
    
    return bFull;
}

int isStackEmpty(Stack *s) {
    int bEmpty;
    
    bEmpty = (s->top == -1);
    
    return bEmpty;
}

int getStackSize(Stack *s) {
    int nSize;
    
    nSize = s->top + 1;
    
    return nSize;
}