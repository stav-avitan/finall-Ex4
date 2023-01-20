#include"Graph.h"

void ShortestRoute(int* adj, int srci, int target, int numOfNodes)
{

    int src = srci;
    int dst = target;
    int n = 0;
    char dump = 0;
    int *res = malloc((numOfNodes) * sizeof(int));
    int *arr = malloc((numOfNodes) * sizeof(int));

    for (int i = 0; i < numOfNodes; i++)
    {
        res[i] = INT_MAX, arr[i] = 0;
    }
    res[src] = 0;

    for (int j = 0; j < numOfNodes - 1; j++)
    {
        n = miLn(res, arr, numOfNodes);
        arr[n] = 1;
        for (int k = 0; k < numOfNodes; k++)
            if (!(arr[k]) && (adj[n* numOfNodes + k]) && (res[n] != INT_MAX) && (res[n] + adj[n * numOfNodes + k] < res[k]))
                res[k] = res[n] + adj[n * numOfNodes + k];
    }
    if (res[dst] == INT_MAX || res[dst] == 0)
    {
        printf("Shortest path: -1");
    }
    else
        printf("Shortest path: %d", res[dst]);

    free(adj);
    free(res);
    free(arr);
}

int miLn(int res[], int arr[], int numOfNodes)
{
    // Initialize min value
    int m = INT_MAX, minV;

    for (int i = 0; i < numOfNodes; i++)
        if (arr[i] == 0 && res[i] <= m)
            m = res[i], minV = i;

    return minV;
}

int dijsktra(struct Graph* head, struct Node* src, struct Node* tar, int numOfNodes)
{
    struct Edge* temp = head->start;
   /* int i, j, n, source, target, min = 999;
    int start, m, d;
    int* visited= malloc((numOfNodes) * sizeof(int));
    int* dist = malloc((numOfNodes) * sizeof(int));
    int* pre = malloc((numOfNodes) * sizeof(int));
    int* path = malloc((numOfNodes) * sizeof(int)); 
    int **cost = malloc((numOfNodes * numOfNodes) * sizeof(int));//need to alloc precise number;*/
    int cost[10][10], i, j, n, source, target, visited[10] = { 0 }, min = 999, dist[10], pre[10];
    int start, m, d, path[10];
    n = numOfNodes;
    source = src->src;
    target = tar->src;
    
    // Input graph
    
    for (i = 1; i <= n; i++)
    {
        for (j = 1; j <= n; j++)
        {
            cost[i][j] = 0;
        }
    }
    while (temp->next != NULL)
    {
        cost[head->start->src][head->start->dest] = head->start->weight;
        temp = temp->next;
    }
    for (int m = 1; m <= n; m++)
    {
        for (int l = 1; l<= n; l++)
        {
            if (cost[m][l] == 0)
                cost[m][l] = 999;
        }
    }
    // logic for dijkstra's aglorithm
    start = source;
    for (i = 1; i <= n; i++)
    {
        dist[i] = 999;  // here we initialize all distances with the maximum value (999) you take any other value also
        pre[i] = -1;   // pre for the previous node 
    }
    visited[source] = 1; // visited source node
    dist[source] = 0;  // distance of first node from first node is 0
    while (visited[target] == 0)
    {
        min = 999;
        m = 0;
        for (i = 1; i <= n; i++)
        {
            d = dist[start] + cost[start][i];   // calcualte the distance from the source
            if (d < dist[i] && visited[i] == 0)
            {
                dist[i] = d;
                pre[i] = start;
            }
            if (min > dist[i] && visited[i] == 0)
            {
                min = dist[i];
                m = i;
            }
        }
        start = m;
        visited[m] = 1;
    }
    // logic for printing path
    start = target;
    j = 0;
    while (start != -1)
    {
        path[j++] = start;
        start = pre[start];
    }
    // printing of the path
    for (i = j - 1; i >= 0; i--)
    {
        if (i != j - 1)
            printf(" to ");
        printf("%d", path[i]);
    }

    printf("\n shortest path is %d", dist[target]);


    free(cost);
    free(visited);
    free(dist);
    free(pre);
    free(path);

    return 0;
}


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
    size_t inputlen = 0, templen = 0;
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
    int flag = 0;
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
    int flag = 0;
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
   shortest_path_dijkstra(src, dst, numOfNodes, InitializeMatrix(g, numOfNodes), src, dst, numOfNodes);

   s= str_slice(s, 6, strlen(s) + 1);

    return s;
}

char* getT(char input[], struct Graph* g, int numOfNodes)
{
    struct newGraph ng;
    int num_nodes = atoi(&(input[2]));
    int num_vertices = numOfNodes;
    int count=4
    int nodes[num];

    while (count-4 < num)
    {
        nodes[count - 4] = input[count];
        count += 2;
    }
    //initilize graph
    ng.num_vertices = numOfNodes;
    shortest_path(InitializeMatrix(g, numOfNodes),num_vertices,nodes,num_nodes)


    input = str_slice(input, 4+2*num, strlen(input) + 1);
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
