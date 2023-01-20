#include"Algo.h"

#define MAX_NODES 100

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

void shortest_path(int* adj_matrix, int num_vertices, int* nodes, int num_nodes) {
    int* dist = (int*)malloc(num_vertices * sizeof(int));
    int* prev = (int*)malloc(num_vertices * sizeof(int));
    int* visited = (int*)calloc(num_vertices, sizeof(int));
    int i, j, u;

    for (i = 0; i < num_vertices; i++) {
        dist[i] = INT_MAX;
        prev[i] = -1;
    }

    dist[nodes[0]] = 0;

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
        if (prev[nodes[i]] == -1) {
            printf("TSP shortest path: %d \n",-1);
            return;
        }
    }

    for (i = 1; i < num_nodes; i++) {
        int current = nodes[i];
        int path[num_vertices];
        int path_size = 0;
        while (current != nodes[0]) {
            path[path_size++] = current;
            current = prev[current];
        }
        path[path_size++] = nodes[0];

        printf("%d", path[path_size - 1]);
        for (j = path_size - 2; j >= 0; j--) {
            printf(" -> %d", path[j]);
        }
        printf("\n");
    }
  }
