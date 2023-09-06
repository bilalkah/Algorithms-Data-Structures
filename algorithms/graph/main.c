#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define SIZE 20

typedef struct node
{
    bool is_valid;
    int hour, minute, price;
} Node;

typedef struct bfs
{
    int city;
    struct bfs *next;
} BFS;

typedef struct queue
{
    BFS *head;
    BFS *tail;
    int hour, minute, stop;
    int price;
    struct queue *next;
} Queue;

Queue *copyPath(Queue *, int, int, int, int);
char **getListIndex(char *, char **, int *, int *);
void findFlight(char *, char *, int, char *, Node **, char **, int, FILE *);
int main(int argc, char *argv[])
{
    FILE *fp;
    char filename[SIZE] = "sample.txt";
    char output[SIZE] = "output.txt";
    char source[SIZE], destination[SIZE], criteria[SIZE];
    int hour, minute, price;
    int i, j, numCities = 0, a, b, numStop;
    char **cityList = NULL;
    Node **adj = NULL;

    printf("Enter the filename: ");
    scanf("%s", filename);

    fp = fopen(filename, "r");
    if (fp == NULL)
    {
        fprintf(stderr, "Error opening file!\n");
        exit(EXIT_FAILURE);
    }
    while (!feof(fp))
    {
        fscanf(fp, "%s %s %d %d %d", &source, &destination, &hour, &minute, &price);
        cityList = getListIndex(source, cityList, &numCities, &i);
        cityList = getListIndex(destination, cityList, &numCities, &j);
    }

    adj = (Node **)malloc(sizeof(Node *) * numCities);
    if (adj == NULL)
    {
        fprintf(stderr, "Error in malloc\n");
        exit(EXIT_FAILURE);
    }
    for (i = 0; i < numCities; i++)
    {
        adj[i] = (Node *)malloc(sizeof(Node) * numCities);
        for (j = 0; j < numCities; j++)
        {
            adj[i][j].is_valid = false;
        }
    }
    fseek(fp, 0, SEEK_SET);
    while (!feof(fp))
    {
        fscanf(fp, "%s %s %d %d %d", &source, &destination, &hour, &minute, &price);
        cityList = getListIndex(source, cityList, &numCities, &i);
        cityList = getListIndex(destination, cityList, &numCities, &j);
        adj[i][j].is_valid = true;
        adj[i][j].hour = hour;
        adj[i][j].minute = minute;
        adj[i][j].price = price;

        adj[j][i].is_valid = true;
        adj[j][i].hour = hour;
        adj[j][i].minute = minute;
        adj[j][i].price = price;
    }
    fclose(fp);

    char newQuery[2] = "y";
    fp = fopen(output, "a");

    while (newQuery[0] == 'y')
    {
        printf("Source: ");
        scanf("%s", source);
        printf("Destination: ");
        scanf("%s", destination);
        printf("Max number of stops: ");
        scanf("%d", &numStop);
        printf("Criteria(time/price): ");
        scanf("%s", criteria);
        findFlight(source, destination, numStop, criteria, adj, cityList, numCities, fp);
        fprintf(fp, "\n");

        printf("\nDo you want to search for another flight? (y/n): ");
        scanf("%s", newQuery);
    }
    fclose(fp);

    for (i = 0; i < numCities; i++)
    {
        free(cityList[i]);
        free(adj[i]);
    }
    free(cityList);
    free(adj);

    return 0;
}

char **getListIndex(char *city, char **cityList, int *size, int *index)
{
    if (cityList == NULL)
    {
        cityList = (char **)malloc(sizeof(char *));
        cityList[0] = (char *)malloc(sizeof(char) * SIZE);
        strncpy(cityList[0], city, SIZE);
        *size = 1;
        *index = 0;
        return cityList;
    }
    int i = 0;
    while (i < *size && strcmp(cityList[i], city) != 0)
    {
        i++;
    }
    if (i == *size)
    {
        cityList = (char **)realloc(cityList, sizeof(char *) * (*size + 1));
        cityList[*size] = (char *)malloc(sizeof(char) * SIZE);
        strncpy(cityList[*size], city, SIZE);
        *size = *size + 1;
        *index = *size - 1;
    }
    else
    {
        *index = i;
    }
    return cityList;
}

/**
 * @brief Find BFS path from source to destination with given criteria time or price and number of stops
 *
 * @param source
 * @param destination
 * @param numStop
 * @param criteria
 * @param adj
 * @param cityList
 * @param numCities
 */
void findFlight(char *source, char *destination, int numStop, char *criteria, Node **adj, char **cityList, int numCities, FILE *fp)
{
    Queue *start = (Queue *)malloc(sizeof(Queue));
    Queue *end = start;
    start->next = NULL;
    start->head = (BFS *)malloc(sizeof(BFS));
    start->tail = start->head;
    start->hour = 0;
    start->minute = 0;
    start->stop = -1;
    start->price = 0;
    cityList = getListIndex(source, cityList, &numCities, &start->head->city);
    start->head->next = NULL;
    Queue *curr = start;
    int dest;
    cityList = getListIndex(destination, cityList, &numCities, &dest);
    int i, j=0;
    while (curr != NULL && curr->stop <= numStop)
    {

        if (curr->tail->city != dest)
        {
            for (i = 0; i < numCities; i++)
            {
                if (adj[curr->tail->city][i].is_valid && i != curr->head->city && i != curr->tail->city)
                {
                    end->next = copyPath(curr, i, adj[curr->tail->city][i].hour, adj[curr->tail->city][i].minute, adj[curr->tail->city][i].price);
                    end = end->next;
                }
            }
        }
        curr = curr->next;
    }
    if (strcmp(criteria, "time") == 0)
    {
        int swapped, i;
        Queue *ptr1;
        Queue *ptr2 = NULL;
        swapped = 1;
        while (swapped)
        {
            swapped = 0;
            ptr1 = start;

            while (ptr1->next != ptr2)
            {
                int left = ptr1->hour * 60 + ptr1->minute;
                int right = ptr1->next->hour * 60 + ptr1->next->minute;
                if (left > right)
                {
                    BFS *head = ptr1->head;
                    BFS *tail = ptr1->tail;
                    int hour = ptr1->hour;
                    int minute = ptr1->minute;
                    int price = ptr1->price;
                    int stop = ptr1->stop;

                    ptr1->head = ptr1->next->head;
                    ptr1->tail = ptr1->next->tail;
                    ptr1->hour = ptr1->next->hour;
                    ptr1->minute = ptr1->next->minute;
                    ptr1->price = ptr1->next->price;
                    ptr1->stop = ptr1->next->stop;

                    ptr1->next->head = head;
                    ptr1->next->tail = tail;
                    ptr1->next->hour = hour;
                    ptr1->next->minute = minute;
                    ptr1->next->price = price;
                    ptr1->next->stop = stop;

                    swapped = 1;
                }
                ptr1 = ptr1->next;
            }
            ptr2 = ptr1;
        }
    }
    else
    {
        int swapped, i;
        Queue *ptr1;
        Queue *ptr2 = NULL;
        swapped = 1;
        while (swapped)
        {
            swapped = 0;
            ptr1 = start;

            while (ptr1->next != ptr2)
            {
                int left = ptr1->price;
                int right = ptr1->next->price;
                if (left > right)
                {
                    BFS *head = ptr1->head;
                    BFS *tail = ptr1->tail;
                    int hour = ptr1->hour;
                    int minute = ptr1->minute;
                    int price = ptr1->price;
                    int stop = ptr1->stop;

                    ptr1->head = ptr1->next->head;
                    ptr1->tail = ptr1->next->tail;
                    ptr1->hour = ptr1->next->hour;
                    ptr1->minute = ptr1->next->minute;
                    ptr1->price = ptr1->next->price;
                    ptr1->stop = ptr1->next->stop;

                    ptr1->next->head = head;
                    ptr1->next->tail = tail;
                    ptr1->next->hour = hour;
                    ptr1->next->minute = minute;
                    ptr1->next->price = price;
                    ptr1->next->stop = stop;

                    swapped = 1;
                }
                ptr1 = ptr1->next;
            }
            ptr2 = ptr1;
        }
    }
    bool found = false;
    curr = start;
    while (curr->next != NULL)
    {
        BFS *temp;
        if (curr->tail->city == dest && curr->stop <= numStop)
        {
            found = true;
            fprintf(fp, "|%s\t|%s\t", source, destination);
            printf("|%s\t|%s\t", source, destination);
            if (curr->stop == 0)
            {
                fprintf(fp, "|None|");
                printf("|None|");
            }
            else
            {
                fprintf(fp, "|");
                printf("|");
                for (temp = curr->head->next; temp != curr->tail; temp = temp->next)
                {
                    fprintf(fp, "%s ", cityList[temp->city]);
                    printf("%s ", cityList[temp->city]);
                }
                fprintf(fp, "|");
                printf("|");
            }
            fprintf(fp, "%d\t|%d\t|%d\n", curr->hour, curr->minute, curr->price);
            printf("%d\t|%d\t|%d\n", curr->hour, curr->minute, curr->price);
        }
        curr = curr->next;
    }
    if (!found)
    {
        fprintf(fp, "|%s\t|%s\t|None\t|None\t|None\n", source, destination);
        printf("No flight found\n");
    }

    while (start)
    {
        Queue *temp = start;
        start = start->next;
        while (temp->head)
        {
            BFS *temp2 = temp->head;
            temp->head = temp->head->next;
            free(temp2);
        }
        free(temp);
    }
}

Queue *copyPath(Queue *curr, int i, int hour, int minute, int price)
{
    Queue *new = (Queue *)malloc(sizeof(Queue));
    new->next = NULL;
    new->stop = curr->stop + 1;
    new->head = (BFS *)malloc(sizeof(BFS));
    new->head->city = curr->head->city;
    BFS *forNew = new->head;
    BFS *forOld = curr->head;

    while (forOld->next != NULL)
    {
        forNew->next = (BFS *)malloc(sizeof(BFS));
        forNew->next->city = forOld->next->city;
        forOld = forOld->next;
        forNew = forNew->next;
    }
    forNew->next = (BFS *)malloc(sizeof(BFS));
    forNew->next->city = i;
    forNew->next->next = NULL;

    new->tail = forNew->next;
    int carry = 0;
    new->minute = (minute + curr->minute);
    if (new->minute >= 60)
    {
        carry = 1;
        new->minute = new->minute % 60;
    }
    new->hour = (hour + curr->hour + carry);
    if (curr->stop != 0)
    {
        new->hour += 1;
    }
    new->price = price + curr->price;
    return new;
}