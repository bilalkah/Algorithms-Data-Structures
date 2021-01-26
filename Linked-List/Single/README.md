# Single Linked List

- node *createNode() : Create new node object
- node *appendList() : Append new node to list. If List is empty, list will be initialized.

## Example
Let starter pointer's name is ***head*** and initialized it ***NULL*** at the beginning.  
head|
----|
0x0|

`head=append(head,5);
`  
head|head->next|
----|----|
5|0x0

`head=append(head,10);
` 
head|head->next|head->next->next|
-|-|-|
5|10|0x0



