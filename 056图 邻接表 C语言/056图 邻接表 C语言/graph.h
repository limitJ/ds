#ifndef _GRAPH_H
#define _GRAPH_H 1
#include "list.h"
#include "set.h"
#include <stdlib.h>
#include <stdbool.h>

typedef struct AdjList_{
    void* vertex;//顶点集
    Set adjacent;//边集
}AdjList;

typedef struct Graph_{
    int vcount;//顶点数量
    int ecount;//边数量
    int (*compare)(const void* key1,const void* key2);
    void (*destroy)(void* data);
    List adjlists;
}Graph;

typedef enum VertexColor_{white,gray,black} VertexColor;

void graph_init(Graph* graph,int (*compare)(const void* key1,const void* key2),void (*destroy)(void* data));

void graph_destroy(Graph* graph);

bool graph_ins_vertex(Graph* graph,const void* data);

bool graph_ins_edge(Graph* graph,const void* data1,const void* data2);

bool graph_rem_vertex(Graph* graph,void** data);

bool graph_rem_edge(Graph* graph,void** data1,void** data2);

int graph_adjlist(const Graph* graph,const void* data,AdjList** adjlist);

int graph_is_adjacent(const Graph* graph,const void* data1,const void* data2);



#endif /* ifndef _GRAPH */
