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

Point NEXT_TO_TOP(Stack *s) {
    if (s->top > 0) {
        //printf("NEXT TO TOP SUCCESS: You are accessing index %ld\n", s->top-1);
        return s->arr[s->top-1];
    } else {
        printf("NEXT TO TOP ERROR: You are trying to access invalid index %ld\n", s->top-1);
        Point error;
        error.x = ERROR;
        error.y = ERROR;
        return error;
    }
}

void PUSH(Stack *s, Point elem) {
    if (!ISFULL(s)) {
        s->arr[++(s->top)] = elem;
        //printf("PUSH SUCCESS: Element {%lf, %lf} pushed as index %ld\n", elem.x, elem.y, s->top);
    } else {
        printf("PUSH ERROR: You are trying to access invalid index %ld\n", s->top+1);
    }
}

Point POP(Stack *s) {
    if (!ISEMPTY(s)) {
        //printf("POP SUCCESS: You are accessing index %ld\n", s->top);
        return s->arr[(s->top)--];
    } else {
        printf("POP ERROR: You are trying to access invalid index %ld\n", s->top);
        Point error;
        error.x = ERROR;
        error.y = ERROR;
        return error;
    }
}

Point TOP(Stack *s) {
    if (!ISEMPTY(s)) {
        //printf("TOP SUCCESS: You are accessing index %ld\n", s->top);
        return s->arr[s->top];
    } else {
        printf("TOP ERROR: You are trying to access invalid index %ld\n", s->top);
        Point error;
        error.x = ERROR;
        error.y = ERROR;
        return error;
    }
}

