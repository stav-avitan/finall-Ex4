#include "Graph.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<limits.h>
#include <ctype.h>
#include "Node.h"
#include "Edge.h"
#define MAX_NODES 100




int* InitializeMatrix(struct Graph* g, int numOfNodes)
{
    int* matrix = malloc((numOfNodes * numOfNodes) * sizeof(int));
    struct Edge* temp;
    struct Node* t = g->head;
    struct Node* ith = NULL;
    struct Node* jth = NULL;
    int ci = 0;
    int cj = 0;

    for (int i = 0; i < numOfNodes; i++)
    {
        for (int j = 0; j < numOfNodes; j++)
        {
            //find the nodes
            ci = 0;
            cj = 0;
            t = g->head;
            //

            while (t != NULL)
            {
                if (i == ci)
                {
                    ith = t;
                }
                if (j == cj)
                {
                    jth = t;
                }
                ci++;
                cj++;
                t = t->next;
            }

            //search for a edge between thw nodes, otherwise -> 0
            temp = g->start;
            while (temp != NULL)
            {
                if (ith->src == jth->src)
                {
                    matrix[i * numOfNodes + j] = 0;
                    break;
                }
                if (temp->src == ith->src && temp->dest == jth->src)
                {
                    matrix[i * numOfNodes + j] = temp->weight;
                    break;
                }
                else
                {
                    matrix[i * numOfNodes + j] = 0;
                }
                temp = temp->next;
            }

        }
    }

    for (int k = 0; k < numOfNodes; k++)
    {
        for (int m = 0; m < numOfNodes; m++)
        {
            printf("%d\t", matrix[k * numOfNodes + m]);
        }
        printf("\n");
    }

    return matrix;
}


char* str_slice(char str[], int slice_from, int slice_to)
{
    // if a string is empty, returns nothing
    if (str[0] == '\0')
        return NULL;

    char* buffer;
    size_t str_len, buffer_len;

    // for negative indexes "slice_from" must be less "slice_to"
    if (slice_to < 0 && slice_from < slice_to) {
        str_len = strlen(str);

        // if "slice_to" goes beyond permissible limits
        if (abs(slice_to) > str_len - 1)
            return NULL;

        // if "slice_from" goes beyond permissible limits
        if (abs(slice_from) > str_len)
            slice_from = (-1) * str_len;

        buffer_len = slice_to - slice_from;
        str += (str_len + slice_from);

        // for positive indexes "slice_from" must be more "slice_to"
    }
    else if (slice_from >= 0 && slice_to > slice_from) {
        str_len = strlen(str);

        // if "slice_from" goes beyond permissible limits
        if (slice_from > str_len - 1)
            return NULL;

        buffer_len = slice_to - slice_from;
        str += slice_from;

        // otherwise, returns NULL
    }
    else
        return NULL;

    buffer = calloc(buffer_len, sizeof(char));
    strncpy(buffer, str, buffer_len);

    return buffer;
}

char* readinput(int* len)
{
    int flag = 1;
    char* input = NULL;
    char tempbuf[200];
    size_t templen = 0;
    do {
        fgets(tempbuf, 200, stdin);
        templen = strlen(tempbuf);
        //input = (char*)malloc((templen+1)*sizeof(char));
        input = (char*)realloc(input, templen + 1);
        strcpy(input, tempbuf);
        //strncat(input, tempbuf, templen);
        //inputlen += templen;
        //tempbuf[200 - 2] = '\n';
        flag = 0;
    } while (flag);
    //printf("%d,%d", *len, templen);
    *len = (int)templen;
    return input;
}


void deleteGraph(struct Graph* g)
{
    struct Node* temp1 = g->head;
    struct Node* delete1;
    struct Edge* temp2 = g->start;
    struct Edge* delete2;

    while (temp1->next != NULL)
    {
        delete1 = temp1;
        temp1 = temp1->next;
        free(delete1);
    }
    free(temp1);

    while (temp2->next != NULL)
    {
        delete2 = temp2;
        temp2 = temp2->next;
        free(delete2);
    }
    free(temp2);

    g->head = NULL;
    g->start = NULL;
}

struct Graph* createGraph(char** input, int strlen)
{ 
    *input = str_slice(*(input), 2, strlen + 1);
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph->head = NULL;
    graph->start = NULL;
    int numOfNodes = atoi(input[0]);
    int curNode = 0;
    int newNodes = 0;
    int i = 0;

    for  (i = 2; i < strlen; i+=2)
    {
        if (*(input[0]+i) == 'n')
        {
            i += 2;
            curNode = atoi(input[0] + i);
            if (graph->head == NULL)
            {
                createHead(graph, curNode);
                newNodes++;
            }
            else
            {
                if (!isNodeExist(graph->head, curNode))
                {
                    createNode(graph->head, curNode);
                    newNodes++;
                }
            }
        }
        else
        {
            if (!isNodeExist(graph->head, atoi(input[0] + i)))
            {
                createNode(graph->head, atoi(input[0] + i));
                newNodes++;
            }
            if (graph->start == NULL)
            {
                createStart(graph, curNode, atoi(input[0] + i), atoi(input[0] + i+2));
            }
            else
            {
                createEdge(graph, curNode, atoi(input[0] + i), atoi(input[0] + i + 2));
            }
            //if node dosent exist create it
            i = i + 2;
        }

        if (*(input[0]+i + 2) == 'B' || *(input[0] + i + 2) == 'A' || *(input[0] + i + 2) == 'D' || *(input[0] + i + 2) == 'S' || *(input[0] + i + 2) == 'T')
        {
            break;
        }
    }

    //test
    if (newNodes == numOfNodes)
    {
        //printf("A - OK nodes");
    }
   *input = str_slice(*(input), i+2, strlen + 1);
    return graph;
}

char* getD(char input[], struct Graph* g)
{
    int toD = atoi(&(input[2]));
    struct Edge* temp = g->start;
    struct Edge* toDelete = NULL;

    removeNode(g->head, toD);
    removeEdge(g->start, toD);

    if (temp->src == toD)
    {
        toDelete = g->start;
        g->start = g->start->next;
        free(toDelete);
    }
    
    while (temp->next != NULL)
    {
        if (temp->next->dest == toD)
        {
            toDelete = temp->next;
            temp->next = temp->next->next;

            free(toDelete); //free Memory of node to delete
        }
        temp = temp->next;
    }


 

    input = str_slice(input,4, strlen(input) + 1);

    return input;
}

char* getB(char input[], struct Graph* g)
{

    int curNode = atoi(&(input[2]));
    //int newNodes = 0;
    int i = 0;

    if (isNodeExist(g->head, atoi(&(input[2]))))
    {
        removeEdge(g->start, curNode);
        //create edge down 
    }
    else
    {
        createNode(g->head, atoi(&(input[2])));
    }

    for (i = 4; i < strlen(input); i += 2)
    {
        
        if (g->start == NULL)
        {
            createStart(g, curNode, atoi(&(input[i])), atoi(&(input[i + 2])));
            i = i + 2;
        }
        else
        {
            createEdge(g, curNode, atoi(&(input[i])), atoi(&(input[i + 2])));
            i = i + 2;
        }

        if (input[i + 2] == 'B' || input[i + 2] == 'A' || input[i + 2] == 'D' || input[i + 2] == 'S' || input[i + 2] == 'T')
        {
            break;
        }
    }

    input = str_slice(input, i+2, strlen(input) + 1);
    return input;
}

char* getS(char s[], struct Graph* g, int numOfNodes)
{
   int src = atoi(&(s[2]));
   int dst = atoi(&(s[4]));
   shortest_path_dijkstra(src, dst, numOfNodes, InitializeMatrix(g, numOfNodes));

   s= str_slice(s, 6, strlen(s) + 1);

    return s;
}

char* getT(char input[], struct Graph* g, int numOfNodes)
{
    int num_nodes = atoi(&(input[2]));
    int count=4;
    int nods [num_nodes];

    while (count-4 < num_nodes)
    {
        nods[count - 4] = input[count];
        count += 2;
    }
    //initilize graph
    shortest_path(InitializeMatrix(g, numOfNodes),numOfNodes,nods,num_nodes);


    input = str_slice(input, 4+2*num_nodes, strlen(input) + 1);
    return input;
}

void OptionManager(char choise, char* input, int lenStr)
{
    struct Graph* graph = NULL;
    int flag = 1;
    int numOfNodes = 0;
    while (flag)
    {
        switch (choise)
        {
        case 'A':
            if (graph != NULL)
            {
                deleteGraph(graph);
            } 
            numOfNodes = atoi(&(input[2]));
            graph = createGraph(&input, lenStr);
            break;
        case 'B':
            input = getB(input, graph);
            numOfNodes++;
            break;
        case 'D':
            input = getD(input, graph);
            numOfNodes--;
            break;
        case 'S':
            input = getS(input, graph, numOfNodes);
            break;
        case 'T':
            printf("still on work");
            //input = 
            break;
        default:
            flag = 0;
            break;
        }

        choise = input[0];
    }

}


void shortest_path_dijkstra(int src, int dest, int num_vertices, int* edges) {
    int* dist = (int*)malloc(num_vertices * sizeof(int));
    int* prev = (int*)malloc(num_vertices * sizeof(int));
    int* visited = (int*)calloc(num_vertices, sizeof(int));
    int i, j;

    for (i = 0; i < num_vertices; i++) {
        dist[i] = INT_MAX;
        prev[i] = -1;
    }

    dist[src] = 0;

    for (i = 0; i < num_vertices; i++) {
        int u = -1;
        int min_dist = INT_MAX;

        for (j = 0; j < num_vertices; j++) {
            if (!visited[j] && dist[j] < min_dist) {
                u = j;
                min_dist = dist[j];
            }
        }

        if (u == -1) {
            break;
        }

        visited[u] = 1;

        for (j = 0; j < num_vertices; j++) {
            if (edges[u*num_vertices + j] && !visited[j]) {
                int new_dist = dist[u] + edges[u*num_vertices + j];
                if (new_dist < dist[j]) {
                    dist[j] = new_dist;
                    prev[j] = u;
                }
            }
        }
    }

    if (prev[dest] == -1) {
        printf("Dijsktra shortest path: %d \n", -1);
        return;
    }

    int current = dest;
    int path[num_vertices];
    int path_size = 0;
    while (current != src) {
        path[path_size++] = current;
        current = prev[current];
    }
    path[path_size++] = src;
    for (i = path_size - 1; i >= 0; i--) {
        printf("Dijsktra shortest path: %d \n", path[i]);
    }
    printf("\n");
}

void shortest_path(int* adj_matrix, int num_vertices, int* nods, int num_nodes) {
    int* dist = (int*)malloc(num_vertices * sizeof(int));
    int* prev = (int*)malloc(num_vertices * sizeof(int));
    int* visited = (int*)calloc(num_vertices, sizeof(int));
    int i, j, u;

    for (i = 0; i < num_vertices; i++) {
        dist[i] = INT_MAX;
        prev[i] = -1;
    }

    dist[nods[0]] = 0;

    for (i = 0; i < num_vertices; i++) {
        int min_dist = INT_MAX;
        for (j = 0; j < num_vertices; j++) {
            if (!visited[j] && dist[j] < min_dist) {
                u = j;
                min_dist = dist[j];
            }
        }

        if (min_dist == INT_MAX) {
            break;
        }

        visited[u] = 1;

        for (j = 0; j < num_vertices; j++) {
            if (adj_matrix[u* num_vertices +j] != -1 && !visited[j]) {
                int new_dist = dist[u] + adj_matrix[u* num_vertices+j];
                if (new_dist < dist[j]) {
                    dist[j] = new_dist;
                    prev[j] = u;
                }
            }
        }
    }

    for (i = 0; i < num_nodes; i++) {
        if (prev[nods[i]] == -1) {
            printf("TSP shortest path: %d \n",-1);
            return;
        }
    }

    for (i = 1; i < num_nodes; i++) {
        int current = nods[i];
        int path[num_vertices];
        int path_size = 0;
        while (current != nods[0]) {
            path[path_size++] = current;
            current = prev[current];
        }
        path[path_size++] = nods[0];

        printf("%d", path[path_size - 1]);
        for (j = path_size - 2; j >= 0; j--) {
            printf(" -> %d", path[j]);
        }
        printf("\n");
    }
}

