#include <stdio.h>
#include <stdbool.h>

#define SIZE 10

static int stack[SIZE];
static int position = -1;

bool isEmpty();
bool isFull();
int peek();
void push(int);
int pop();

int main()
{

    printf("%d\n", peek());
    push(5);
    printf("%d\n", peek());
    push(10);
    push(20);
    push(70);
    while (!isEmpty())
    {
        printf("%d ", pop());
    }
    int i = 10;
    while (!isFull())
    {
        push(++i);
    }
    printf("\n%d \n", position);

    while (!isEmpty())
    {
        printf("%d ", pop());
    }

    return 0;
}

bool isEmpty()
{
    if (position != -1)
    {
        return false;
    }
    return true;
}

bool isFull()
{
    if (position != SIZE - 1)
    {
        return false;
    }
    return true;
}

int peek()
{
    if (isEmpty())
    {
        printf("Stack is Empty! Cannot peek\n");
        return -1;
    }
    return stack[position];
}

void push(int value)
{
    if (isFull())
    {
        printf("Stack is Full! Cannot push\n");
        return;
    }
    stack[++position] = value;
}

int pop()
{
    if (isEmpty())
    {
        printf("Stack is Empty! Cannot pop\n");
        return -1;
    }
    return stack[position--];
}
