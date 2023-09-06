/**
 * @file SocialNetwork.c
 * @author Bilal Kahraman (l1117062@std.yildiz.edu.tr)
 * @brief odev3.pdf
 * @version 0.1
 * @date 2021-01-07
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct graph
{
    int id;
    int centrality;
    int following;
    int follower;
    int distance;
    struct graph *next;
    struct graph **adj;
} GRAPH;

typedef struct Link
{
    GRAPH *vertex;
    int distance;
    struct Link *next;
} link;

static GRAPH *head;
static link *start;

link *createNode(GRAPH *, int);
void linkNodes(link *);
void dijkstra(int);
GRAPH *createGraph(int);
GRAPH *add2Graph(int, int *);
void maxHeapify(int **, int, int);
int **heapSort(int **, int);
int **createUserFollowing(int **, int, int *);
int **createUserFollower(int **, int, int *);
int **createUserCentrality(int **, int);
void makeAdj(GRAPH *, GRAPH *);
void destroyGraph();
void readCSV(int *);

int main()
{
    GRAPH *p;
    int totalUser = 0, **userFollowing, **userFollower, **userCentrality, **userTotal, avgFollower = 0, avgFollowing = 0, i, totalCentrality = 0;
    //read csv file and create graph
    readCSV(&totalUser);
    printf("Number of user: %d\n", totalUser);

    /**
     * create user id,user following/follower/total_connection number matrix
     *  |user id            |user id            |...
     *  |---------------------------------------------
     *  |# of user following|# of user following|...
     */
    userFollowing = createUserFollowing(userFollowing, totalUser, &avgFollowing);
    userFollower = createUserFollower(userFollower, totalUser, &avgFollower);

    userTotal = (int **)malloc(sizeof(int *) * 2);
    if (userTotal == NULL)
    {
        fprintf(stderr, "main(), malloc error\n");
        exit(EXIT_FAILURE);
    }
    for (i = 0; i < 2; i++)
    {
        userTotal[i] = (int *)malloc(sizeof(int) * totalUser);
        if (userTotal[i] == NULL)
        {
            fprintf(stderr, "main(), malloc error\n");
            exit(EXIT_FAILURE);
        }
    }
    for (i = 0; i < totalUser; i++)
    {
        userTotal[0][i] = userFollower[0][i];
        userTotal[1][i] = userFollower[1][i] + userFollowing[1][i];
    }

    printf("\n");
    printf("Ordered by following number\n");
    userFollowing = heapSort(userFollowing, totalUser);
    for (i = totalUser - 1; i > totalUser - 11; i--)
    {
        printf("%d\t: %d\n", userFollowing[0][i], userFollowing[1][i]);
    }
    printf("Average : %d\n", avgFollowing / totalUser);
    printf("Median  : %d\n", userFollowing[1][totalUser / 2]);

    userFollower = heapSort(userFollower, totalUser);
    printf("\n");
    printf("Ordered by follower number\n");
    for (i = totalUser - 1; i > totalUser - 11; i--)
    {
        printf("%d\t: %d\n", userFollower[0][i], userFollower[1][i]);
    }
    printf("Average : %d\n", avgFollower / totalUser);
    printf("Median  : %d\n", userFollower[1][totalUser / 2]);


    userTotal = heapSort(userTotal, totalUser);
    printf("\n");
    printf("Ordered by total connection\n");
    for (i = totalUser - 1; i > totalUser - 11; i--)
    {
        printf("%d\t %d\n", userTotal[0][i], userTotal[1][i]);
    }
    printf("Average : %d\n", (avgFollower + avgFollowing) / totalUser);
    printf("Median  : %d\n", userTotal[1][totalUser / 2]);

    for (i = 0; i < 2; i++)
    {
        free(userFollowing[i]);
        free(userFollower[i]);
        free(userTotal[i]);
    }
    free(userFollowing);
    free(userFollower);
    free(userTotal);

    //find the shortest path
    dijkstra(totalUser);

    //calculate centrality
    userCentrality = createUserCentrality(userCentrality, totalUser);
    userCentrality = heapSort(userCentrality, totalUser);
    printf("Ordered by betweenness centrality measure\n");

    for (i = 0; i < totalUser; i++)
    {
        totalCentrality += userCentrality[1][i];
    }
    for (i = totalUser - 1; i > totalUser - 11; i--)
    {
        float temp = (float)userCentrality[1][i] / (float)totalCentrality;
        printf("%d\t: %f\n", userCentrality[0][i], temp);
    }

    for (i = 0; i < 2; i++)
    {
        free(userCentrality[i]);
    }
    free(userCentrality);

    destroyGraph();

    return 0;
}

/**
 * @brief Create a Graph object
 * 
 * @param id 
 * @return GRAPH* 
 */
GRAPH *createGraph(int id)
{
    GRAPH *p = (GRAPH *)malloc(sizeof(GRAPH));
    if (p == NULL)
    {
        fprintf(stderr, "createGRAPH(), malloc error\n");
        exit(EXIT_FAILURE);
    }
    p->id = id;
    p->following = 0;
    p->centrality = 0;
    p->follower = 0;
    p->distance = INT_MAX;
    p->next = NULL;
    p->adj = NULL;
    return p;
}

/**
 * @brief To check id whether if it has already been in the graph or not. If not, function will create new node and icrease totalUser.
 * Function return address' of id 
 * 
 * @param id 
 * @param totalUser 
 * @return GRAPH* 
 */
GRAPH *add2Graph(int id, int *totalUser)
{
    GRAPH *p, *t;
    for (p = head; p != NULL && p->id != id; t = p, p = p->next)
        ;
    if (p == NULL)
    {
        *totalUser += 1;
        p = createGraph(id);
        if (head == NULL)
        {
            head = p;
        }
        else
        {
            t->next = p;
        }
    }
    return p;
}

/**
 * @brief To make connection between nodes. If nodes have already connected(linear search), then function wont do anything.
 * If follower node's does not have and adjancecy it will allocate one block with malloc(), if it has, it will reallocate +1 block with realloc()
 * Following node's follower number and follower node's following number will increase.
 * 
 * @param follower 
 * @param followed 
 */
void makeAdj(GRAPH *follower, GRAPH *followed)
{
    int i;
    for (i = 0; i < follower->following; i++)
    {
        if (follower->adj[i] == followed)
        {
            return;
        }
    }
    follower->following++;
    if (follower->adj == NULL)
    {
        follower->adj = (GRAPH **)malloc(sizeof(GRAPH *));
        if (follower->adj == NULL)
        {
            fprintf(stderr, "makeAdj(), malloc error\n");
            exit(EXIT_FAILURE);
        }
    }
    else
    {
        follower->adj = (GRAPH **)realloc(follower->adj, follower->following * sizeof(GRAPH *));
    }
    follower->adj[follower->following - 1] = followed;
    followed->follower++;
}

/**
 * @brief Free allocated memory for graph
 * From the beginning to end, deallocate adjancency array of all nodes. After then, deallocated all nodes.
 * If we deallocate node and node's adjancency array, then second node and node's adjancency array, then third ....
 * Memory leak could occur. Because we can lose the next pointer 
 */
void destroyGraph()
{
    GRAPH *p;
    for (p = head; p != NULL; p = p->next)
    {
        free(p->adj);
        p->adj = NULL;
    }
    while (head)
    {
        p = head;
        head = head->next;
        free(p);
    }
}

/**
 * @brief Read csv file and and create graph
 * Take file name from the user as input
 * read the first line of file
 * then read follower comma followed order,after then find address' of id add2Graph(follower,totalUser) in the graph and make connection makeAdj(follower,followed)
 * @param totalUser 
 */
void readCSV(int *totalUser)
{

    FILE *fp;
    char filename[20];
    char comma;
    int follower, followed;
    GRAPH *fr = NULL, *fd = NULL;

    printf("Write the file name: ");
    //scanf("%s", &filename);
    fp = fopen("SNAgraph.csv", "r");
    if (fp == NULL)
    {
        fprintf(stderr, "%s file could not opened\n", filename);
        exit(EXIT_FAILURE);
    }

    fscanf(fp, "%s", &filename);

    while (!feof(fp))
    {
        fscanf(fp, "%d %c %d", &follower, &comma, &followed);
        fr = add2Graph(follower, totalUser);
        fd = add2Graph(followed, totalUser);
        makeAdj(fr, fd);
        fr = NULL;
        fd = NULL;
    }
    fclose(fp);
}

/**
 * @brief Max-Heapify for HeapSort function()
 * 
 * @param arr 
 * @param n 
 * @param i 
 */
void maxHeapify(int **arr, int n, int i)
{
    int largest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;

    if (l < n && arr[1][l] > arr[1][largest])
    {
        largest = l;
    }

    if (r < n && arr[1][r] > arr[1][largest])
    {
        largest = r;
    }

    if (largest != i)
    {
        int temp = arr[0][i];
        arr[0][i] = arr[0][largest];
        arr[0][largest] = temp;

        temp = arr[1][i];
        arr[1][i] = arr[1][largest];
        arr[1][largest] = temp;

        maxHeapify(arr, n, largest);
    }
}

/**
 * @brief sort array from small to large by 1. index of row
 * 
 * @param arr 
 * @param n 
 * @return int** 
 */
int **heapSort(int **arr, int n)
{
    int i;
    for (i = n / 2 - 1; i >= 0; i--)
    {
        maxHeapify(arr, n, i);
    }

    for (i = n - 1; i > 0; i--)
    {
        int temp = arr[0][0];
        arr[0][0] = arr[0][i];
        arr[0][i] = temp;

        temp = arr[1][0];
        arr[1][0] = arr[1][i];
        arr[1][i] = temp;

        maxHeapify(arr, i, 0);
    }
    return arr;
}

/**
 * @brief Create a User Following Array and return it
 * 
 * @param userArray matrix pointer for id and following number
 * @param totalUser total number of user in the graph
 * @param avgFollowing total following number 
 * @return int** 
 */
int **createUserFollowing(int **userArray, int totalUser, int *avgFollowing)
{
    GRAPH *p;
    int i, j, k;
    userArray = (int **)malloc(sizeof(int *) * 2);
    if (userArray == NULL)
    {
        fprintf(stderr, "createUserFollowing(), malloc error\n");
        exit(EXIT_FAILURE);
    }
    for (i = 0; i < 2; i++)
    {
        userArray[i] = (int *)malloc(sizeof(int) * totalUser);
        if (userArray[i] == NULL)
        {
            fprintf(stderr, "createUserFollowing(), malloc error\n");
            exit(EXIT_FAILURE);
        }
    }
    for (i = 0, p = head; p != NULL; p = p->next, i++)
    {
        userArray[0][i] = p->id;
        userArray[1][i] = p->following;
        (*avgFollowing) += userArray[1][i];
    }
    return userArray;
}

/**
 * @brief Create a User Follower Array and return it
 * 
 * @param userArray 
 * @param totalUser 
 * @param avgFollower 
 * @return int** 
 */
int **createUserFollower(int **userArray, int totalUser, int *avgFollower)
{
    GRAPH *p;
    int i, j, k;
    userArray = (int **)malloc(sizeof(int *) * 2);
    if (userArray == NULL)
    {
        fprintf(stderr, "createUserFollower(), malloc error\n");
        exit(EXIT_FAILURE);
    }
    for (i = 0; i < 2; i++)
    {
        userArray[i] = (int *)malloc(sizeof(int) * totalUser);
        if (userArray[i] == NULL)
        {
            fprintf(stderr, "createUserFollower(), malloc error\n");
            exit(EXIT_FAILURE);
        }
    }
    for (i = 0, p = head; i < totalUser; i++, p = p->next)
    {
        userArray[0][i] = p->id;
        userArray[1][i] = p->follower;
        (*avgFollower) += userArray[1][i];
    }
    return userArray;
}

/**
 * @brief Create a User Centrality Array and return it
 * 
 * @param userCentrality 
 * @param totalUser 
 * @return int** 
 */
int **createUserCentrality(int **userCentrality, int totalUser)
{
    GRAPH *p;
    int i;
    userCentrality = (int **)malloc(sizeof(int *) * 2);
    if (userCentrality == NULL)
    {
        fprintf(stderr, "createUserCentrality(), malloc error\n");
        exit(EXIT_FAILURE);
    }
    for (i = 0; i < 2; i++)
    {
        userCentrality[i] = (int *)malloc(sizeof(int) * totalUser);
        if (userCentrality[i] == NULL)
        {
            fprintf(stderr, "createUserCentrality(), malloc error\n");
            exit(EXIT_FAILURE);
        }
    }
    for (i = 0, p = head; i < totalUser; i++, p = p->next)
    {
        userCentrality[0][i] = p->id;
        userCentrality[1][i] = p->centrality;
    }
    return userCentrality;
}

/**
 * @brief to make connection between link nodes
 * 
 * @param node 
 */
void linkNodes(link *node)
{
    link *p;
    if (start == NULL)
    {
        start = node;
        return;
    }
    for (p = start; p->next != NULL; p = p->next)
        ;
    p->next = node;
}

/**
 * @brief Create a Node object. It contains information distance(dist) of graph node (node) from start(static link *start)
 * 
 * @param node 
 * @param dist 
 * @return link* 
 */
link *createNode(GRAPH *node, int dist)
{
    link *p = (link *)malloc(sizeof(link));
    if (p == NULL)
    {
        fprintf(stderr, "createQueue(), malloc error\n");
        exit(EXIT_FAILURE);
    }
    p->vertex = node;
    p->distance = dist;
    p->next = NULL;
    return p;
}

/**
 * @brief   start beginning of the head until NULL
 *          put node in list of link and make distance 0
 *          then go to node's adjancency and compare if node's adjancency distance is INT_MAX or not. 
 *          If INT_MAX, then calculate node's adjancency distance as node's distance+1 and append to list.
 *          If it is not equal INT_MAX, then there is already a short path for it. Because all path's length is 1
 *          0 distance symbolize starting point of traversal, so for an instance 0->1->2 or 5->6->7
 *          And also always append adjancency's of node to list. 
 *          For example, Let A is starting point of graph and we put it to list
 *          list : A->NULL
 *      distance : 0
 *          then we will continue on list and we will check A's adjancency: B and C
 *          list: A->B->C->NULL
 *     distance : 0  1  1 
 *          then lets check B's adjancency: D and E
 *         list : A->B->C->D->E->NULL 
 *     distance : 0  1  1  2  2    
 *          So here A->B->D and A->B->E there is betweenness centrality for B node
 *          So condition to increase centrality if node's adjancency's distance is equal to INT_MAX and node's distance>=1
 *          when we arrive the end of list, we will save the information of node's and distance to distance.txt file and path' to path.txt file and
 *          make node's distance is INT_MAX and deallocate memory of list.
 *          There is also a progress bar to visualize to speed of function
 * @param totalUser 
 */
void dijkstra(int totalUser)
{
    GRAPH *p;
    link *q, *t;
    int i, time = 0, k = 0;
    FILE *fp,*ptr;
    fp = fopen("distance.txt", "w");
    ptr = fopen("path.txt","w");
    printf("Dijkstra Calculating...\n");
    printf("[                                                  ]\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b");
    for (p = head; p != NULL; p = p->next)
    {
        linkNodes(createNode(p, 0));
        q = start;
        while (q)
        {
            for (i = 0; i < q->vertex->following; i++)
            {
                if (q->vertex->adj[i]->distance == INT_MAX)
                {
                    q->vertex->adj[i]->distance = q->vertex->distance + 1;
                    linkNodes(createNode(q->vertex->adj[i], q->distance + 1));
                    if (q->distance >= 1)
                    {
                        q->vertex->centrality++;
                    }
                    fprintf(ptr,"%d -> %d : %d\n",q->vertex->id,q->vertex->adj[i]->id,q->distance+1);
                }
            }
            q = q->next;
        }
        fprintf(ptr,"==========================================\n");
        for (q = start; q != NULL; q = q->next)
        {
            fprintf(fp, "%d -> %d\t: %d\n", start->vertex->id, q->vertex->id, q->distance);
        }
        fprintf(fp, "==========================================\n");
        while (start)
        {
            start->vertex->distance = INT_MAX;
            q = start;
            start = start->next;
            free(q);
        }
        time++;
        for (; k < 50 * (time - 0) / (totalUser); k++)
        {
            printf("=");
        }
    }
    fclose(ptr);
    fclose(fp);
    printf("\nIt is done. You can check the file distance.txt\n");
}
