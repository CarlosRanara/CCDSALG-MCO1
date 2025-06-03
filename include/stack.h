/**
 * stack.h
 * Stack data structure implementation for Graham's Scan algorithm
 * Group 16 - CCDSALG Term 3, AY 2024-2025
 * 
 * Programmers: [Your Group Member Names]
 * Code Testers: [Your Group Member Names]
 */

#ifndef STACK_H
#define STACK_H

#include <stdio.h>

#define MAX_STACK_SIZE 32768

typedef struct {
    double x;
    double y;
} Point;

typedef struct {
    Point items[MAX_STACK_SIZE];
    int top;
} Stack;

/**
 * Creates a new empty stack
 * @param s Pointer to the stack to be created
 */
void createStack(Stack *s);

/**
 * Pushes an element onto the stack
 * @param s Pointer to the stack
 * @param elem The element to push
 * @param bSuccess Pointer to a flag indicating success
 */
void pushToStack(Stack *s, Point elem, int *bSuccess);

/**
 * Pops an element from the stack
 * @param s Pointer to the stack
 * @param elem Pointer to store the popped element
 * @param bSuccess Pointer to a flag indicating success
 */
void popFromStack(Stack *s, Point *elem, int *bSuccess);

/**
 * Returns the top element of the stack without removing it
 * @param s Pointer to the stack
 * @param elem Pointer to store the top element
 * @param bSuccess Pointer to a flag indicating success
 */
void getTopOfStack(Stack *s, Point *elem, int *bSuccess);

/**
 * Returns the element below the top element (NEXT-TO-TOP operation)
 * This is essential for Graham's Scan algorithm
 * @param s Pointer to the stack
 * @param elem Pointer to store the element below the top
 * @param bSuccess Pointer to a flag indicating success
 */
void getNextToTopOfStack(Stack *s, Point *elem, int *bSuccess);

/**
 * Checks if the stack is full
 * @param s Pointer to the stack
 * @return 1 if full, 0 otherwise
 */
int isStackFull(Stack *s);

/**
 * Checks if the stack is empty
 * @param s Pointer to the stack
 * @return 1 if empty, 0 otherwise
 */
int isStackEmpty(Stack *s);

/**
 * Returns the number of elements in the stack
 * @param s Pointer to the stack
 * @return The number of elements
 */
int getStackSize(Stack *s);

#endif /* STACK_H */