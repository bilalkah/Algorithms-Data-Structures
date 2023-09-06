#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Data
{
  int key;
  int data;
} data;

data *table;
int primeNumber;

int hashCode(int);
bool isPrime(int);
int getPrime(int);
void table_init(int);
void insert(int, int);
int search(int);
bool delete (int);
void printHashTable();

int main()
{

  table_init(10);

  insert(10, 26);
  insert(41, 36);
  insert(20, 47);
  printHashTable();

  printf("Search : %d\n", search(41));
  delete (41);
  printHashTable();

  free(table);
  return 0;
}

int hashCode(int key)
{
  return key % primeNumber;
}

bool isPrime(int value)
{
  if (value <= 2)
  {
    return false;
  }
  int i = value / 2;
  while (i >= 2)
  {
    if (value % i == 0)
    {
      return false;
    }
    i--;
  }
  return true;
}

int getPrime(int size)
{
  while (!isPrime(size))
  {
    size++;
  }
  return size;
}

void table_init(int size)
{
  primeNumber = getPrime(size);
  table = (data *)malloc(primeNumber * sizeof(data));
  if (table == NULL)
  {
    fprintf(stderr, "table_init, malloc error line: %d\n", __LINE__);
    exit(EXIT_FAILURE);
  }
  for (int i = 0; i < primeNumber; i++)
  {
    table[i].data = 0;
    table[i].key = 0;
  }
}

void insert(int key, int data)
{
  int hashKey = hashCode(key);
  if (table[hashKey].key == 0)
  {
    table[hashKey].key = key;
    table[hashKey].data = data;
  }
  else if (table[hashKey].key == key)
  {
    table[hashKey].data = data;
  }
  else
  {
    printf("Collision occured\n");
  }
}

int search(int key)
{
  int hashKey = hashCode(key);
  if (table[hashKey].key == key)
  {
    return table[hashKey].data;
  }
  printf("Key did not match\n");
  return -1;
}

bool delete (int key)
{
  int hashKey = hashCode(key);
  if (table[hashKey].key == key)
  {
    table[hashKey].key = 0;
    table[hashKey].data = 0;
    return true;
  }
  printf("Key did not match\n");
  return false;
}

void printHashTable()
{
  for (int i = 0; i < primeNumber; i++)
  {
    if (table[i].key == 0)
    {
      printf("HashTable[%d] /\n", i);
    }
    else
    {
      printf("Key : %d Data : %d\n", table[i].key, table[i].data);
    }
  }
}