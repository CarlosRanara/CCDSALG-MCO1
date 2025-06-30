#include <stdio.h>

#ifndef MAX

    /*
        Max size of stack array
    */
    #define MAX 32768
    #define ERROR -999

    /*
        Struct for stack array
    */
    typedef struct {
        int arr[MAX];
        int top;
    } Stack;


   /*
        Prototypes for stack operations
   */
    void CREATE(Stack *s);
    void PUSH(Stack *s, int elem);
    int POP(Stack *s);
    int TOP(Stack *s);
    int ISFULL(Stack *s);
    int ISEMPTY(Stack *s);
    int NEXT_TO_TOP(Stack *s);


#endif