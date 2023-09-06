#include <stdio.h>
#include <stdlib.h>

typedef struct list
{
    int val;
    struct list *next;
    struct list *prev;
} node;

node *createNode(int);
node *appendList(node *, int);
node *insertList(node *, int, int);
void printListNext(node *);
void printListPrev(node *);
void deleteList(node *);

int main()
{

    node *head = NULL;

    head = appendList(head, 1);
    head = appendList(head, 2);
    head = appendList(head, 3);
    head = appendList(head, 4);
    head = appendList(head, 5);
    head = appendList(head, 6);
    head = appendList(head, 7);
    head = appendList(head, 8);
    head = appendList(head, 9);
    head = appendList(head, 10);

    printListNext(head);
    printListPrev(head);

    head = insertList(head, 0, 2);
    head = insertList(head, 0, 6);

    printListNext(head);
    printListPrev(head);

    deleteList(head);

    return 0;
}

/**
 * @brief Create a Node object
 * 
 * @param value 
 * @return node* 
 */
node *createNode(int value)
{
    node *p = (node *)malloc(sizeof(node));
    if (p == NULL)
    {
        fprintf(stderr, "Error *createNode(): Malloc allocation\n");
        exit(EXIT_FAILURE);
    }
    p->val = value;
    p->next = NULL;
    p->prev = NULL;
    return p;
}

/**
 * @brief Append new node to list
 * 
 * @param head 
 * @param value 
 * @return node* 
 */
node *appendList(node *head, int value)
{
    node *p, *temp;
    if (head == NULL)
    {
        head = createNode(value);
        head->next = head;
        head->prev = head;
        return head;
    }

    temp = createNode(value);
    temp->next = head;
    head->prev->next = temp;
    temp->prev = head->prev;
    head->prev = temp;

    return head;
}

/**
 * @brief Insert new node to list after where value
 * 
 * @param head 
 * @param value 
 * @param where 
 * @return node* 
 */
node *insertList(node *head, int value, int where)
{
    if (head == NULL)
    {
        printf("List is empty!!\n");
        return head;
    }
    node *p, *temp;
    for (p = head; p->val != where && p->next != head; p = p->next)
        ;

    if (p->next == head)
    {
        printf("%d could not found\n", where);
        return head;
    }
    temp = createNode(value);
    temp->next = p->next;
    temp->prev = p;
    p->next = temp;
    temp->next->prev = temp;
    return head;
}

void printListNext(node *head)
{
    printf("p -> next\n");
    node *p = head;
    if (head->next == head)
    {
        printf("%d", head->val);
        printf(" -> ");
    }
    for (; p->next != head; p = p->next)
    {
        printf("%d", p->val);
        if (p->next != head)
        {
            printf(" -> ");
        }
    }
    printf("%d\n\n", p->val);
}

void printListPrev(node *head)
{
    printf("p -> prev\n");
    node *p = head->prev;
    if (p->prev == head)
    {
        printf("%d", head->val);
        printf(" -> ");
    }
    for (; p->prev != head->prev; p = p->prev)
    {
        printf("%d", p->val);
        printf(" -> ");
    }
    printf("%d\n\n", p->val);
}

void deleteList(node *head)
{
    node *p;
    if (head->next == head)
    {
        free(head);
        return;
    }
    head->prev->next = NULL;
    while (head)
    {
        p = head;
        head = head->next;
        free(p);
    }
}