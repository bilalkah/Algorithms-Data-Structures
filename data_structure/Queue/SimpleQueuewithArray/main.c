#include <stdio.h>
#include <stdbool.h>

#define SIZE 10

static int queue[SIZE];
static int front = -1;
static int rear = -1;
static int size = 0;

bool isEmpty();
bool isFull();
int peek();
void enqueue(int);
int dequeue();

int main()
{

    while (!isFull())
    {
        enqueue(10);
    }

    printf("%d \n", dequeue());
    printf("%d \n", dequeue());
    printf("%d \n", dequeue());

    while (!isFull())
    {
        enqueue(9);
    }
    printf("%d \n", dequeue());
    printf("%d \n", dequeue());
    printf("%d \n", dequeue());
    printf("%d \n", dequeue());
    printf("%d \n", dequeue());
    printf("%d \n", dequeue());

    while (!isFull())
    {
        enqueue(8);
    }

    while (!isEmpty())
    {
        printf("%d ", dequeue());
    }

    return 0;
}

bool isEmpty()
{
    return size == 0;
}
bool isFull()
{
    return size == SIZE;
}
int peek()
{
    if (isEmpty())
    {
        printf("Queue is Empty! Cannot peek\n");
        return -1;
    }
    return queue[front];
}
void enqueue(int value)
{
    if (isFull())
    {
        printf("Queue is Full! Cannot Enqueue\n");
        return;
    }
    if (rear == -1 || front == -1)
    {
        rear = 0;
        front = 0;
        size++;
        queue[rear] = value;
        return;
    }
    rear = (rear + 1) % SIZE;
    size++;
    queue[rear] = value;
}
int dequeue()
{
    if (isEmpty())
    {
        printf("Queue Empty! Cannot Dequeue\n");
        return -1;
    }
    int returnValue = queue[front];
    queue[front] = 0;
    front = (front + 1) % SIZE;
    size--;
    if (size == 0)
    {
        front = -1;
        rear = -1;
    }
    return returnValue;
}
