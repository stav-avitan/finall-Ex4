#pragma once
#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include"Graph.h"

struct Node
{
    int src;
    struct Node* next;
};

void createHead(struct Graph* head, int src);
void createNode(struct Node* head, int src);
void updateNode(struct Node* head, int srcToUpdate);
void removeNode(struct Node* head, int toDelete);
int isNodeExist(struct Node* head, int isExist);

