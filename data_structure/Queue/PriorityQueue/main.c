//Heap data structure

#include <stdio.h>

#define SIZE 15

static int size;

void swap(int *, int *);
void maxHeapify(int[], int);
void minHeapify(int[], int);
void insert(int[], int);
int extract(int[]);
void increaseKey(int[], int, int);
void decreaseKey(int[], int, int);
int peek(int[]);
void delete (int[], int);
void printQueue(int[]);

int main()
{

    static int queue[SIZE];

    insert(queue, 60);
    insert(queue, 15);
    insert(queue, 70);
    insert(queue, 91);
    insert(queue, 5);
    insert(queue, 74);
    insert(queue, 48);
    insert(queue, 5);

    printQueue(queue);

    increaseKey(queue, 2, 21);
    decreaseKey(queue, 1, 60);

    printQueue(queue);

    printf("Extract : %d\n", extract(queue));
    printf("Extract : %d\n", extract(queue));

    printQueue(queue);

    insert(queue, 2);
    insert(queue, 100);

    printQueue(queue);

    delete (queue, 2);
    printQueue(queue);

    return 0;
}

void swap(int *val1, int *val2)
{
    int b = *val1;
    *val1 = *val2;
    *val2 = b;
}

void maxHeapify(int array[], int index)
{
    int largest = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;

    if (left < size && array[left] > array[largest])
    {
        largest = left;
    }
    if (right < size && array[right] > array[largest])
    {
        largest = right;
    }

    if (largest != index)
    {
        swap(&array[index], &array[largest]);
        maxHeapify(array, largest);
    }
}

void minHeapify(int array[], int index)
{
    int smallest = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;

    if (left < size && array[left] < array[smallest])
    {
        smallest = left;
    }
    if (right < size && array[right] < array[smallest])
    {
        smallest = right;
    }

    if (smallest != index)
    {
        swap(&array[index], &array[smallest]);
        minHeapify(array, smallest);
    }
}

void insert(int array[], int value)
{
    if (size == SIZE)
    {
        printf("Priority Queue is Full! Cannot insert\n");
        return;
    }
    array[size++] = value;
    if (size > 1)
    {
        for (int i = size / 2 - 1; i >= 0; i--)
        {
            maxHeapify(array, i);
        }
    }
}

int extract(int array[])
{
    int returnValue = array[0];
    array[0] = array[--size];
    maxHeapify(array, 0);

    return returnValue;
}

void increaseKey(int array[], int index, int amount)
{
    array[index] += amount;
    for (int i = size / 2 - 1; i >= 0; i--)
    {
        maxHeapify(array, i);
    }
}

void decreaseKey(int array[], int index, int amount)
{
    array[index] -= amount;
    for (int i = index; i >= 0; i--)
    {
        maxHeapify(array, i);
    }
}

int peek(int array[])
{
    return array[0];
}

void delete (int array[], int index)
{
    array[index] = array[--size];
    for (int i = index; i >= 0; i--)
    {
        maxHeapify(array, i);
    }
}

void printQueue(int array[])
{
    for (int i = 0; i < size; i++)
    {
        printf("%d ", array[i]);
    }
    printf("\n");
}