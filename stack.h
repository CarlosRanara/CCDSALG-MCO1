/* ============================================================================
 * FILE: stack.h
 * Stack Data Structure Header
 * Programmer: [Your Name]
 * Tester: [Your Name]
 * ============================================================================ */
#ifndef STACK_H
#define STACK_H

#define MAX_STACK_SIZE 32768

struct pointTag {
    double x;
    double y;
};
typedef struct pointTag pointType;

struct stackTag {
    pointType data[MAX_STACK_SIZE];
    int nTop;
};
typedef struct stackTag stackType;

void createStack(stackType *pS);
void pushStack(stackType *pS, pointType elem);
pointType popStack(stackType *pS);
pointType topStack(stackType *pS);
pointType nextToTopStack(stackType *pS);
int isFullStack(stackType *pS);
int isEmptyStack(stackType *pS);

#endif