#pragma once
#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include"Graph.h"

struct Edge {
    int src, dest, weight;
    struct Edge* next;
};

void createStart(struct Graph* start, int src, int dest, int weight);
void createEdge(struct Graph* start, int src, int dest, int weight);
void updateEdge(struct Edge* head, int src);
int isEdgeExist(struct Edge* head, int src);
void removeEdge(struct Edge* head, int src);
