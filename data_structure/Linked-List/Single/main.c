#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    int value;
    struct Node *next;
} node;

node *createNode(int);
node *appendList(node *, int);
node *prependList(node *, int);
node *insertList(node *, int, int);
node *deleteElement(node *, int);
void printList(node *);
void deleteList(node *);

int main()
{

    node *head = NULL;

    head = prependList(head, 85);
    printList(head);
    head = appendList(head, 5);
    head = appendList(head, 6);
    head = appendList(head, 10);
    head = appendList(head, 1);
    head = appendList(head, 7);
    head = appendList(head, 95);

    printList(head);

    head = prependList(head, 21);

    printList(head);

    head = prependList(head, 22);
    printList(head);

    head = insertList(head, 31, 7);
    printList(head);

    head = deleteElement(head, 100);
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

/**
 * @brief Prepend val to list
 * 
 * @param head 
 * @param val 
 * @return node* 
 */
node *prependList(node *head, int val)
{
    node *p = createNode(val);
    if (head == NULL)
    {
        return p;
    }
    p->next = head;
    return p;
}

/**
 * @brief Insert val to list after where
 * 
 * @param head 
 * @param val 
 * @param where 
 * @return node* 
 */
node *insertList(node *head, int val, int where)
{
    node *p;
    for (p = head; p != NULL && p->value != where; p = p->next)
        ;
    if (p == NULL)
    {
        printf("%d not exists.\n", where);
        return head;
    }
    node *t = createNode(val);
    t->next = p->next;
    p->next = t;
    return head;
}

/**
 * @brief Delete selected node of list
 * 
 * @param head 
 * @param val 
 * @return node* 
 */
node *deleteElement(node *head, int val)
{
    node *p, *prev;
    for (p = head; p != NULL && p->value != val; prev = p, p = p->next)
        ;
    if (p == NULL)
    {
        printf("%d not exists.\n", val);
        return head;
    }
    if (p == head)
    {
        head = head->next;
        free(p);
        return head;
    }
    prev->next = p->next;
    free(p);
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
    printf("\n");
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