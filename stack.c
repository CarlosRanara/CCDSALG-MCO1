#include <stdio.h>
#include "stack.h"

void CREATE(Stack *s) {
    s->top = -1;
}

int ISEMPTY(Stack *s) {
    return s->top < 0;
}

int ISFULL(Stack *s) {
    return s->top >= MAX - 1;
}

int NEXT_TO_TOP(Stack *s) {
    if (s->top > 0) {
        printf("NEXT TO TOP SUCCESS: You are accessing index %d\n", s->top-1);
        return s->arr[s->top-1];
    } else {
        printf("NEXT TO TOP ERROR: You are trying to access invalid index %d\n", s->top-1);
        return ERROR;
    }
}

void PUSH(Stack *s, int elem) {
    if (!ISFULL(s)) {
        s->arr[++(s->top)] = elem;
        printf("PUSH SUCCESS: Element %d pushed as index %d\n", elem, s->top);
    } else {
        printf("PUSH ERROR: You are trying to access invalid index %d\n", s->top+1);
    }
}

int POP(Stack *s) {
    if (!ISEMPTY(s)) {
        printf("POP SUCCESS: You are accessing index %d\n", s->top);
        return s->arr[(s->top)--];
    } else {
        printf("POP ERROR: You are trying to access invalid index %d\n", s->top);
        return ERROR;
    }
}

int TOP(Stack *s) {
    if (!ISEMPTY(s)) {
        printf("TOP SUCCESS: You are accessing index %d\n", s->top);
        return s->arr[s->top];
    } else {
        printf("TOP ERROR: You are trying to access invalid index %d\n", s->top);
        return ERROR;
    }
}

