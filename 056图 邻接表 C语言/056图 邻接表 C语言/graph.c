#include "graph.h"
#include <stdlib.h>
#include <memory.h>
#include "list.h"
#include "set.h"
#define NULL ((void*)0)
void graph_init(Graph* graph,int (*compare)(const void* key1,const void* key2),void (*destroy)(void* data)){
    graph->vcount = 0;
    graph->ecount = 0;
    graph->compare = compare;
    graph->destroy = destroy;
    list_init(&graph->adjlists,compare, NULL);
}

void graph_destroy(Graph* graph){
    AdjList* adjList;
    while ((&graph->adjlists)->size > 0) {
        if (list_rem_next(&graph->adjlists, NULL, (void **) &adjList) == true) {
            list_destroy(&adjList->adjacent);
            if (graph->destroy != NULL) {
                graph->destroy(adjList->vertex);
            }
            free(adjList);
        }
    }
    list_destroy(&graph->adjlists);
    memset(graph, 0, sizeof(Graph));
}


bool graph_ins_vertex(Graph* graph,const void* data){
    ListElmt* element;
    AdjList* adjList;
    //先遍历一遍 看看顶点是否存在
    for (element = (&graph->adjlists)->head; element != NULL; element = element->next) {
        if (graph->compare(data,((AdjList*)element->data)->vertex)){
            return true;
        }
    }

    //添加顶点
    adjList = (AdjList *) malloc(sizeof(AdjList));
    if (adjList == NULL) {
        return false;
    }
    adjList->vertex = (void*)data;
    set_init(&adjList->adjacent, graph->compare, NULL);
    if (list_ins_next(&graph->adjlists, (&graph->adjlists)->tail, adjList) != true) {
        return false;
    }
    graph->vcount++;
    return true;
}

bool graph_ins_edge(Graph* graph,const void* data1,const void* data2){
    ListElmt* element;
    for (element = (&graph->adjlists)->head; element != NULL; element = element->next) {
        if (graph->compare(data2,((AdjList*)element->data)->vertex)){
            break;
        }
    }
    if (element == NULL) {
        return false;
    }
    for (element = (&graph->adjlists)->head; element != NULL; element = element->next){
        if (graph->compare(data1,((AdjList*)element->data)->vertex)){
            break;
        }
    }
    if (element == NULL) {
        return false;
    }
    if (add(&((AdjList *) element->data)->adjacent, data2) != true) {
        return false;
    }
    graph->ecount++;
    return true;
}

bool graph_rem_vertex(Graph* graph,void** data){
    ListElmt* element, *temp = NULL,*prev;
    AdjList *adjList = NULL;
    int found = 0;
    prev = NULL;
    for (element = (&graph->adjlists)->head; element != NULL; element = element->next){
        //如果删除的顶点 还有边联系的话 就不允许删
        if (in(&((AdjList*)element->data)->adjacent,*data)){
            return false;
        }
        if (graph->compare(*data,((AdjList*)element->data)->vertex)){
            temp = element;
            found=1;
        }
        if (!found){
            prev = element;
        }
    }
    if (!found){
        return false;
    }
    if ((&((AdjList *) temp->data)->adjacent)->size > 0) {
        return false;
    }
    if (list_rem_next(&graph->adjlists, prev, (void **) &adjList) != true) {
        return false;
    }
    if (adjList != NULL) {
        *data = adjList->vertex;
    }
    free(adjList);
    graph->vcount--;
    return true;
}


bool graph_rem_edge(Graph* graph,void** data1,void** data2){
    ListElmt* element;
    for (element = (&graph->adjlists)->head; element != NULL; element = element->next){
        if (graph->compare(data1,((AdjList*)element->data)->vertex)){
            break;
        }
    }
    if (element == NULL) {
        return false;
    }
    if (del(&((AdjList *) element->data)->adjacent, data2) != true) {
        return false;
    }
    graph->ecount--;
    return true;
}

//取出邻接点
int graph_adjlist(const Graph* graph,const void* data,AdjList** adjlist){
    ListElmt* element,*prev = NULL;
    for (element = (&graph->adjlists)->head; element != NULL; element = element->next){
        if (graph->compare(data,((AdjList*)element->data)->vertex)){
            break;
        }
        prev = element;
    }
    if (element == NULL) {
        return false;
    }
    *adjlist = element->data;
    return 0;
}

int graph_is_adjacent(const Graph* graph,const void* data1,const void* data2){
    ListElmt* element,*prev = NULL;
    for (element = (&graph->adjlists)->head; element != NULL; element = element->next){
        if (graph->compare(data1,((AdjList*)element->data)->vertex)){
            break;
        }
        prev = element;
    }
    if (element == NULL) {
        return false;
    }

    return in(&((AdjList *) element->data)->adjacent, data2);
}
