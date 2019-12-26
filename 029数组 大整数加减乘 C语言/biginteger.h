//
// Created by zhubin on 2019/3/31.
//

#ifndef BIGINTEGER_BIGINTEGER_H
#define BIGINTEGER_BIGINTEGER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
#include <assert.h>
#define byte char
#define SIZE 100//精度100
#define new(Object) (Object*)malloc(sizeof(Object))
#define throwException(e) fputs(e,stderr)
typedef struct BigInteger{
    byte data[SIZE];
    int size;
    char ch;
}BigInteger;
BigInteger* create(byte* data);
BigInteger* add(BigInteger* a,BigInteger* b);
BigInteger* mult(BigInteger*a ,BigInteger* b);
BigInteger* sub(BigInteger* a,BigInteger* b);
void bigsqrts(char* a,char *ans);
int comp(BigInteger* a,BigInteger* b);
void print(BigInteger* num);
#endif //BIGINTEGER_BIGINTEGER_H
