#pragma once
#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include <limits.h>

void shortest_path_dijkstra(int src, int dest, int num_vertices, int* edges);
void shortest_path(int* adj_matrix, int num_vertices, int* nodes, int num_nodes);