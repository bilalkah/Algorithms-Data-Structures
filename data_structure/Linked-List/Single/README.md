# Single Linked List

- node *createNode(int val) : Create new node object
- node *appendList(node *head, int val) : Append new node to list. If List is empty, list will be initialized.
- node *prependList(node *head, int val) : Prepend new node to list.
- node *insertList(node *head, int val, int where) : Insert new node to list after where value.
- node *deleteElement(node *head, int val) : Delete selected element from list.

## Example
Let starter pointer's name is ***head*** and initialized it ***NULL*** at the beginning.  
head|
----|
0x0|

`head=appendList(head,5);
`  
head|head->next|
----|----|
5|0x0

`head=appendList(head,10);
` 
head|head->next|head->next->next|
-|-|-|
5|10|0x0

`head=prependList(head,3);
`  
head|head->next|head->next->next|head->next->next->next|
-|-|-|-|
3|5|10|0x0

`head=insertList(head,16,5);
`
head|head->next|head->next->next|head->next->next->next|head->next->next->next->next|
-|-|-|-|-|
3|5|16|10|0x0

`head=deleteElement(head,5);
`
head|head->next|head->next->next|head->next->next->next|
-|-|-|-|
3|16|10|0x0
