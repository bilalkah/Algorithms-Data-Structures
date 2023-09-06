Yildiz Technical University
Data Structure and Algorithms 
1. Quiz
C Programming Language
11/12/2020

#Creating matrix with sigly-linked-list
```explanation
x and y are indexes of the matrix and val is the value of the matrix at that index
```
```example
  
x: 0
y: 0
val: 20
20 
   
   
x: 1
y: 1
val: 15
20 -> 0   
|    |    
V    V    
0 -> 15


x: 2
y: 3
val: 10
20 -> 0 -> 0 -> 0
|    |    |    |
V    V    V    V
0 -> 15 -> 0 -> 0
|    |    |    |
V    V    V    V
0 -> 0 -> 0 -> 10


x: 0
y: 7
val: 35
20 -> 0 -> 0 -> 0 -> 0 -> 0 -> 0 -> 35
|    |    |    |
V    V    V    V
0 -> 15 -> 0 -> 0
|    |    |    |
V    V    V    V    
0 -> 0 -> 0 -> 10


x: 9
y: 1
val: 40
20 -> 0 -> 0 -> 0 -> 0 -> 0 -> 0 -> 35
|    |    |    |
V    V    V    V
0 -> 15 -> 0 -> 0
|    |    |    |
V    V    V    V
0 -> 0 -> 0 -> 10
|    |
V    V
0 -> 0
|    |
V    V
0 -> 0
|    |
V    V
0 -> 0
|    |
V    V
0 -> 0
|    |
V    V
0 -> 0
|    |
V    V
0 -> 0
|    |
V    V
0 -> 40
```
