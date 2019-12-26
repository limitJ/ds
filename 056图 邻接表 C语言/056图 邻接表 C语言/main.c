#include <stdio.h>
#include "graph.h"
int compare(const void* key1,const void* key2);
void destroy(void* data);
int main(int argc, char *argv[])
{
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph_init(graph, compare, destroy);

    return 0;
}
int compare(const void* key1,const void* key2){
    return *(int*)key1 - *(int*)key2;
}
void destroy(void* data){
    //NULL
}