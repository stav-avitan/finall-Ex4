#ifndef GRAPH_
#define GRAPH_
#include <stdio.h>
#include <stdlib.h>
#include<string.h>

#define CHUNK 200

struct Node
{
    int src;
    struct Node* next;
};

struct Edge {
    int src, dest, weight;
    struct Edge* next;
};

struct Graph
{
    struct Node* head;
    struct Edge* start;
};
#include"Edge.h"
#include"Node.h"

//new dijestra
//Algo File
//all other
int* InitializeMatrix(struct Graph* , int );
char* str_slice(char str[], int , int );
char* readinput(int* len);
char* getD(char input[], struct Graph* );
char* getB(char input[], struct Graph* );
char* getS(char s[], struct Graph* , int );
char* getT(char input[], struct Graph* , int );
void OptionManager(char , char* , int );
void deleteGraph(struct Graph* );
struct Graph* createGraph(char** , int );
void shortest_path_dijkstra(int , int , int , int* );
void shortest_path(int* , int , int* , int );



#endif