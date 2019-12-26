#include <stdio.h>
#include <stdlib.h>
#include "sparsematrix.h"
#define len(arr) sizeof(arr)/sizeof(arr[0])
int main(void){
    TSMatrix *A = (TSMatrix *) malloc(sizeof(TSMatrix));
    TSMatrix *Q = (TSMatrix *) malloc(sizeof(TSMatrix));
    int matrix[6][7]={
            {0,12,9,0,0,0,0},
            {0,0,0,0,0,0,0},
            {-3,0,0,0,0,14,0},
            {0,0,24,0,0,0,0},
            {0,18,0,0,0,0,0},
            {15,0,0,-7,0,0,0}
    };
    CreateSMatrix(A, matrix, len(matrix), len(matrix[0]));
    FastTransposeSMatrix(A, Q);
    PrintSMatrix(Q);
    free(A);
    free(Q);
    return 0;
}