/* ============================================================================
 * FILE: stack.c
 * Stack Data Structure Implementation - Fully C99 Procedural Compliant
 * Programmer: [Your Name]
 * Tester: [Your Name]
 * ============================================================================ */
#include "stack.h"

/* Creates an empty stack - initializes top to -1 */
void createStack(stackType *pS) {
    pS->nTop = -1;
}

/* Pushes an element onto the stack if not full */
void pushStack(stackType *pS, pointType elem) {
    int bIsFull;
    
    bIsFull = isFullStack(pS);
    if (bIsFull == 0) {
        pS->nTop++;
        pS->data[pS->nTop] = elem;
    }
}

/* Pops and returns the top element from the stack */
pointType popStack(stackType *pS) {
    pointType elem;
    int bIsEmpty;
    
    elem.x = 0.0;
    elem.y = 0.0;
    
    bIsEmpty = isEmptyStack(pS);
    if (bIsEmpty == 0) {
        elem = pS->data[pS->nTop];
        pS->nTop--;
    }
    
    return elem;
}

/* Returns the top element without removing it */
pointType topStack(stackType *pS) {
    pointType elem;
    int bIsEmpty;
    
    elem.x = 0.0;
    elem.y = 0.0;
    
    bIsEmpty = isEmptyStack(pS);
    if (bIsEmpty == 0) {
        elem = pS->data[pS->nTop];
    }
    
    return elem;
}

/* Returns the element below the top element (NEXT-TO-TOP operation) */
pointType nextToTopStack(stackType *pS) {
    pointType elem;
    
    elem.x = 0.0;
    elem.y = 0.0;
    
    if (pS->nTop > 0) {
        elem = pS->data[pS->nTop - 1];
    }
    
    return elem;
}

/* Checks if the stack is full */
int isFullStack(stackType *pS) {
    int nResult;
    
    nResult = 0;
    if (pS->nTop == MAX_STACK_SIZE - 1) {
        nResult = 1;
    }
    
    return nResult;
}

/* Checks if the stack is empty */
int isEmptyStack(stackType *pS) {
    int nResult;
    
    nResult = 0;
    if (pS->nTop == -1) {
        nResult = 1;
    }
    
    return nResult;
}