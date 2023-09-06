#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>

typedef struct stack
{
    char val;
    struct stack *next;
} stack;

bool isEmpty(stack *order)
{
    if (order == NULL)
    {
        return true;
    }
    return false;
}

char peek(stack *order)
{
    return order->val;
}

int precedence(char ch)
{
    if (ch == '(' || ch == ')')
    {
        return 4;
    }
    if (ch == '^')
    {
        return 3;
    }
    if (ch == '*' || ch == '/')
    {
        return 2;
    }
    if (ch == '+' || ch == '-')
    {
        return 1;
    }

    return 0;
}

stack *push(stack *order, char ch)
{
    stack *p = (stack *)malloc(sizeof(stack));
    if (order == NULL)
    {
        p->next = NULL;
        p->val = ch;
        order = p;
        return order;
    }
    p->next = order;
    p->val = ch;
    order = p;
    return order;
}

stack *pop(stack *order, char *ans)
{
    if (isEmpty(order))
    {
        fprintf(stderr, "Stack is empty\n");
        return NULL;
    }
    *ans = order->val;
    stack *p = order;
    order = order->next;
    free(p);
    return order;
}

char *convert(char *ch)
{

    stack *order = NULL;
    int i, n, j = 0;
    char temp;
    n = strlen(ch);
    char *ans = (char *)malloc(sizeof(char) * (n + 1));
    ans[n] = '\0';
    for (i = 0; i < n; i++)
    {
        if (isdigit(ch[i]))
        {
            ans[j++] = ch[i];
        }
        else
        {
            if (order == NULL)
            {
                order = push(order, ch[i]);
            }
            else
            {
                if (ch[i] == ')')
                {
                    while (peek(order) != '(')
                    {
                        order = pop(order, &temp);
                        ans[j++] = temp;
                    }
                    order = pop(order, &temp);
                    order = pop(order, &temp);
                    ans[j++] = temp;
                }
                else
                {
                    while (!isEmpty(order) && precedence(order->val) != 4 && precedence(order->val) >= precedence(ch[i]))
                    {
                        order = pop(order, &temp);
                        ans[j++] = temp;
                    }
                    order = push(order, ch[i]);
                }
            }
        }
    }

    while (order)
    {
        order = pop(order, &temp);
        ans[j++] = temp;
    }
    return ans;
}

int main()
{

    char *ch, *ans;

    ch = (char *)malloc(sizeof(char) * 128);
    if (ch == NULL)
    {
        printf("malloc error\n");
        exit(EXIT_FAILURE);
    }
    scanf("%s",ch);
    //strcpy(ch, "2^3/(2+3*5^(2-3))-2");
    ch[strlen(ch)] = '\0';

    printf("%s\n", ch);
    ans = convert(ch);
    ans[strlen(ans)] = '\0';
    printf("%s", ans);
    free(ch);
    free(ans);
    return 0;
}