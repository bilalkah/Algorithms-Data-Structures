#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//Size of stack
#define MAX 6

typedef struct Stack
{
    int value;
    struct Stack *next;
} stack;

//Number of element in stack
static int count;

bool isEmpty(stack *);
bool isFull(stack *);
int peek(stack *);
stack *push(stack *, int);
stack *pop(stack *, int *);

int main()
{

    stack *LIFO = NULL;
    int val;

    LIFO = push(LIFO, 10);
    LIFO = push(LIFO, 15);
    LIFO = push(LIFO, 22);
    LIFO = push(LIFO, 36);
    LIFO = push(LIFO, 20);
    LIFO = push(LIFO, 16);

    printf("Peek from stack: %d\n",peek(LIFO));
    LIFO = push(LIFO, 37);

    while (!isEmpty(LIFO))
    {
        LIFO = pop(LIFO, &val);
        printf("%d ", val);
    }

    return 0;
}

/**
 * @brief Check stack is empty or not
 * 
 * @param LIFO 
 * @return true 
 * @return false 
 */
bool isEmpty(stack *LIFO)
{
    if (LIFO == NULL)
    {
        return true;
    }
    return false;
}

/**
 * @brief Check stack is full or not
 * 
 * @param LIFO 
 * @return true 
 * @return false 
 */
bool isFull(stack *LIFO)
{
    if (count == MAX)
    {
        return true;
    }
    return false;
}

/**
 * @brief Peek last value 
 * 
 * @param LIFO 
 * @return int 
 */
int peek(stack *LIFO)
{
    return LIFO->value;
}

/**
 * @brief Push value to stack
 * 
 * @param LIFO 
 * @param val 
 * @return stack* 
 */
stack *push(stack *LIFO, int val)
{
    if (isFull(LIFO))
    {
        printf("Stack is Full!\n");
        return LIFO;
    }
    stack *p = (stack *)malloc(sizeof(stack));
    p->value = val;
    p->next = LIFO;
    count++;
    return p;
}

/**
 * @brief Pop value from stack
 * 
 * @param LIFO 
 * @param val 
 * @return stack* 
 */
stack *pop(stack *LIFO, int *val)
{
    if (isEmpty(LIFO))
    {
        printf("Stack is Empty!\n");
        (*val) = -1;
        return LIFO;
    }
    (*val) = LIFO->value;
    stack *p = LIFO;
    LIFO = LIFO->next;
    free(p);
    count--;
    return LIFO;
}