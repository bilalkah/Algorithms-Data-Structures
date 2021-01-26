# Doubly Circular Linked List
- node *createNode(int value) : Create new node object.
- node *appendList(node *head, int value) : Append new node object to list. If list is empty, it will be initialized.
- node *insertList(node *head, int value, int where) : Insert new node object to list after a value that given.  



## Example
Append number from 1 to 4  
head|head->next|head->next->next|head->next->next->next|
-|-|-|-|
1|2|3|4|  
---
head|head->prev|head->prev->prev|head->prev->prev->prev|
-|-|-|-|
1|4|3|2|

`head=insertList(head,6,2)
`