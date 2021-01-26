#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    int value;
    struct Node *next;
} node;

node *createNode(int);
node *appendList(node *, int);
void printList(node *);
void deleteList(node *);

int main()
{

    node *head = NULL;

    head = appendList(head, 5);
    head = appendList(head, 6);
    head = appendList(head, 10);
    head = appendList(head, 1);
    head = appendList(head, 7);
    head = appendList(head, 95);

    printList(head);

    deleteList(head);
    return 0;
}

/**
 * @brief Create a Node object
 * 
 * @param val 
 * @return node* 
 */
node *createNode(int val)
{
    node *p = (node *)malloc(sizeof(node));
    if (p == NULL)
    {
        fprintf(stderr, "addList(), malloc error\n");
        exit(EXIT_FAILURE);
    }
    p->next = NULL;
    p->value = val;
    return p;
}

/**
 * @brief Append val to list
 * 
 * @param head 
 * @param val 
 * @return node* 
 */
node *appendList(node *head, int val)
{
    node *p = createNode(val);
    if (head == NULL)
    {
        head = p;
        return head;
    }
    node *t;
    for (t = head; t->next != NULL; t = t->next)
        ;
    t->next = p;
    return head;
}

void printList(node *head)
{
    node *p;
    for (p = head; p != NULL; p = p->next)
    {
        printf("%d", p->value);
        if (p->next != NULL)
        {
            printf("->");
        }
    }
}

void deleteList(node *head)
{
    node *p;
    while (head)
    {
        p = head;
        head = head->next;
        free(p);
    }
}