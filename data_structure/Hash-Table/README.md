# Hash Table

## Functions
- int hashCode(int key) : Generate hash code for given key. Call getPrime() 
- bool isPrime(int value) : Check value is prime or not.
- int getPrime(int size) : Generate prime number. Call isPrime()
- void table_init(int size) : Initialize hash table with zero.
- void insert(int key, int data) : Insert data to the index of the key.
- int search(int key) : Search data using key.
- bool delete(int key) : Delete data using key.
- void printHashTable() : Print Hash Table.

``
table_init(5);
``
| |0|1|2|3|4|
|-|-|-|-|-|-|
|key|0|0|0|0|0|
|data|0|0|0|0|0|
---
``
insert(28,20);
`` 
>28 mod 5 = 3
```
table[3].key == 0
It is avaible to insert data.
```
| |0|1|2|3|4|
|-|-|-|-|-|-|
|key|0|0|0|28|0|
|data|0|0|0|20|0|
---
``
insert(30,10);
``
>30 mod 5 = 0

| |0|1|2|3|4|
|-|-|-|-|-|-|
|key|30|0|0|28|0|
|data|10|0|0|20|0|
---
``
insert(2,19);
``
>2 mod 5 = 2

| |0|1|2|3|4|
|-|-|-|-|-|-|
|key|30|0|2|28|0|
|data|10|0|19|20|0|
---
``
insert(60,58);
``
>60 mod 5 = 0
```
table[0].key != key (30!=60)
Collision occured.
```
---
``
delete(30);
``
>30 mod 5 = 0
```
table[0].key == key (30==30)
```
| |0|1|2|3|4|
|-|-|-|-|-|-|
|key|0|0|2|28|0|
|data|0|0|19|20|0|
---
``
delete(7);
``
>7 mod 5 = 2

```
table[2].key != key (7!=2)
Key did not match
```

---
``
search(28)
``
```
hashCode(28)==3
table[3].key == key (28==28)
function will return table[3].data (20)
```