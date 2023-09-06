# Prioriy Queue with Heap Data Structure
- void swap(int *val1, int *val2) : Swap values between two variable via reference.
- void maxHeapify(int array[], int index) : Builder of Max-Priority Queue. Compares child nodes with parent and swap value between bigger child and parent.
- void minHeapify(int array[], int index) : Builder of Min-Priority Queue. Compares child node with parent and swap value between smaller child and parent.
- void insert(int array[], int value) : Insert new value to Priorty Queue and call maxHeapify/minHeapify to build queue.
- int extract(int array[]) : Extract Max/Min Value from Max/Min Priority Queue and call maxHeapify/minHeapify. 
- void increaseKey(int array[], int index, int amount) : Increase the value in the given index by the given amount
- void decreaseKey(int array[], int index, int amount) : Decrease the value in the given index by the given amount
- int peek(int array[]) : Peek Max/Min value from queue.
- void delete (int array[], int index) : Delete node from queue where selected index.
- void printQueue(int array[]) : Print queue.

---

```
insert(queue,60);
insert(queue,15);
insert(queue,70);
insert(queue,91);
insert(queue,5);
insert(queue,74);
insert(queue,48);
insert(queue,5);
```
|0|1|2|3|4|5|6|7|
|-|-|-|-|-|-|-|-|
|91|70|74|15|5|60|48|5|
---
```
increaseKey(queue,2,21);
decreaseKey(queue,1,60);
```
|0|1|2|3|4|5|6|7|
|-|-|-|-|-|-|-|-|
|95|15|91|10|5|60|48|5|
---
```
printf("Extract : %d\n",extract(queue));
printf("Extract : %d\n",extract(queue));
```
``
Extract : 95
Extract : 91
``
|0|1|2|3|4|5|
|-|-|-|-|-|-|
|60|15|48|10|5|5|
---
```
insert(queue,2);
insert(queue,100);
```

|0|1|2|3|4|5|6|7|
|-|-|-|-|-|-|-|-|
|100|60|48|15|5|5|2|10|
---

```
delete(queue,2);
```
|0|1|2|3|4|5|6|
|-|-|-|-|-|-|-|
|100|60|10|15|5|5|2|