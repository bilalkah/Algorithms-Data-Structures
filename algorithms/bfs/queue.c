#include <stdio.h>
#include <stdlib.h>

typedef struct Tree
{
    int value;
    struct Tree *right;
    struct Tree *left;
} node;

typedef struct Order
{
    node *tree;
    struct Order *next;
} order;

typedef struct Queue
{
    order *front;
    order *rear;
} queue;

node *createNode(int val)
{
    node *p = (node *)malloc(sizeof(node));
    if (p == NULL)
    {
        fprintf(stderr, "createNode malloc error\n");
        exit(EXIT_FAILURE);
    }
    p->value = val;
    p->right = NULL;
    p->left = NULL;
    return p;
}

order *createOrder(node *root)
{
    order *p = (order *)malloc(sizeof(order));
    if (p == NULL)
    {
        fprintf(stderr, "createQueue malloc error\n");
        exit(EXIT_FAILURE);
    }
    p->tree = root;
    p->next = NULL;
    return p;
}

node *linkNodes(node *root, int val)
{
    if (root == NULL)
    {
        return createNode(val);
    }
    if (val > root->value)
    {
        root->right = linkNodes(root->right, val);
    }
    else if (val < root->value)
    {
        root->left = linkNodes(root->left, val);
    }

    return root;
}

void destroyTree(node *root)
{
    if (root == NULL)
    {
        return;
    }
    destroyTree(root->left);
    destroyTree(root->right);
    free(root);
}

void enqueue(queue *kuyruk)
{
    if (kuyruk->front->tree->left != NULL)
    {
        order *p = createOrder(kuyruk->front->tree->left);
        kuyruk->rear->next = p;
        kuyruk->rear = p;
    }
    if (kuyruk->front->tree->right != NULL)
    {
        order *p = createOrder(kuyruk->front->tree->right);
        kuyruk->rear->next = p;
        kuyruk->rear = p;
    }
}

int dequeue(queue *kuyruk)
{
    if (kuyruk->front == NULL)
    {
        return -1;
    }
    order *p = kuyruk->front;
    int returnValue = p->tree->value;
    kuyruk->front = kuyruk->front->next;
    free(p);
    return returnValue;
}

void breadthFirst(queue *kuyruk)
{
    int count = 1, i, returnValue;
    /*
    enqueue(kuyruk);
    returnValue = dequeue(kuyruk);
    printf("%d ", returnValue);
    */
    while (kuyruk->front != NULL)
    {
        enqueue(kuyruk);
        returnValue = dequeue(kuyruk);
        printf("%d ", returnValue);
        /*
        count *= 2;
        for (i = 0; i < count; i++)
        {
            enqueue(kuyruk);
        }

        for (i = 0; i < count / 2; i++)
        {
            returnValue = dequeue(kuyruk);
            if (returnValue != -1)
            {
                printf("%d ", returnValue);
            }
        }*/
    }
}

int main()
{

    node *root = NULL;

    root = linkNodes(root, 10);
    root = linkNodes(root, 6);
    root = linkNodes(root, 20);
    root = linkNodes(root, 9);
    root = linkNodes(root, 1);
    root = linkNodes(root, 15);
    root = linkNodes(root, 25);

    if (root != NULL)
    {
        order *start = createOrder(root);
        queue kuyruk;
        kuyruk.front = start;
        kuyruk.rear = start;

        breadthFirst(&kuyruk);
    }

    destroyTree(root);

    return 0;
}
