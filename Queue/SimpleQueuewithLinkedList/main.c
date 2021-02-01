#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 10

//Data that we want to hold
typedef struct Data
{
    int value;
    struct Data *next;
} data;

//Queue data structure
typedef struct Queue
{
    int size;
    data *front;
    data *rear;
} queue;

static queue FIFO;

data *createData(int);
bool isEmpty();
bool isFull();
int peek();
void enqueue(int);
int dequeue();
void emptyQueue();

int main()
{

    enqueue(5);
    enqueue(10);
    enqueue(14);
    enqueue(20);

    printf("%d\n", peek());
    while (!isEmpty())
    {
        printf("%d ", dequeue());
    }
    printf("\n");
    while (!isFull())
    {
        enqueue(rand() % 100);
    }
    enqueue(98);

    while (!isEmpty())
    {
        printf("%d ", dequeue());
    }
    printf("\n");
    printf("%d\n", dequeue());

    enqueue(10);
    enqueue(5);
    enqueue(19);
    printf("%d\n", dequeue());
    enqueue(32);
    printf("%d\n", dequeue());

    emptyQueue();

    return 0;
}

data *createData(int value)
{
    data *p = (data *)malloc(sizeof(data));
    if (p == NULL)
    {
        fprintf(stderr, "createData malloc error\n");
        exit(EXIT_FAILURE);
    }
    p->value = value;
    p->next = NULL;
    return p;
}

bool isEmpty()
{
    if (FIFO.size == 0)
    {
        return true;
    }
    return false;
}

bool isFull()
{
    if (FIFO.size == MAX)
    {
        return true;
    }
    return false;
}

int peek()
{
    if (isEmpty())
    {
        printf("Queue is Empty! Cannot peek\n");
        return -1;
    }
    return FIFO.front->value;
}

void enqueue(int value)
{
    if (isFull())
    {
        printf("Queue is Full! Cannot enqueue\n");
        return;
    }
    data *p = createData(value);
    if (FIFO.front == NULL)
    {
        FIFO.front = p;
        FIFO.rear = p;
        FIFO.size++;
        return;
    }
    FIFO.rear->next = p;
    FIFO.rear = p;
    FIFO.size++;
}

int dequeue()
{
    if (isEmpty())
    {
        printf("Queue is Empty! Cannot dequeue\n");
        return -1;
    }
    int returnValue = FIFO.front->value;
    data *temp = FIFO.front;
    FIFO.front = FIFO.front->next;
    free(temp);
    FIFO.size--;
    return returnValue;
}

void emptyQueue()
{
    while (!isEmpty())
    {
        int garbage = dequeue();
    }
}