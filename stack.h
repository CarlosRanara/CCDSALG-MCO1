#ifndef STACK
#define STACK

    /*
        Max size of stack array
    */
    #define MAX 32768
    #define ERROR -999

    /*
        Struct for coordinates
    */
    typedef struct {
        double x;
        double y;
    } Point;

    /*
        Struct for stack array
    */
    typedef struct {
        Point arr[MAX];
        int top;
    } Stack;


   /*
        Prototypes for stack operations
   */
    void CREATE(Stack *s);
    void PUSH(Stack *s, Point elem);
    Point POP(Stack *s);
    Point TOP(Stack *s);
    int ISFULL(Stack *s);
    int ISEMPTY(Stack *s);
    Point NEXT_TO_TOP(Stack *s);


#endif

