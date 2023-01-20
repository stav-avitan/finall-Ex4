#pragma once
#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include"Algo.h"
#include"Edge.h"
#include"Node.h"

#define CHUNK 200

struct Graph
{
    struct Node* head;
    struct Edge* start;
};

//old jijktra
void ShortestRoute(int* adj, int srci, int target, int numOfNodes);
int miLn(int res[], int arr[], int numOfNodes);
int dijsktra(struct Graph* head, struct Node* src, struct Node* tar, int numOfNodes);
//new dijestra
//Algo File
//all other
int* InitializeMatrix(struct Graph* g, int numOfNodes);
char* str_slice(char str[], int slice_from, int slice_to);
char* readinput(int* len);
char* getD(char input[], struct Graph* g);
char* getB(char input[], struct Graph* g);
char* getS(char s[], struct Graph* g, int numOfNodes);
char* getT(char input[], struct Graph* g, int numOfNodes);
void OptionManager(char choise, char* input, int lenStr);
void deleteGraph(struct Graph* g);
struct Graph* createGraph(char** input, int strlen);



