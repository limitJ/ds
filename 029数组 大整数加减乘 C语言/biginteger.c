//
// Created by zhubin on 2019/3/31.
//

#include "biginteger.h"

void show(BigInteger* num, int pos);

BigInteger* create(byte* data){
    BigInteger* bigInteger = new(BigInteger);
    if (bigInteger == NULL) {
        throwException("创建失败！");
        return NULL;
    }
    bigInteger->size = strlen(data);
    for (int i = 0; i < SIZE; ++i) {
        if(i<strlen(data)){
            bigInteger->data[i] = data[strlen(data)-i-1];
        } else{
            bigInteger->data[i] = '0';
        }
    }
    return bigInteger;
}
BigInteger* add(BigInteger*a ,BigInteger* b) {
    BigInteger *sum = create("");
    if(a->ch=='-'&&b->ch=='-'){
        sum->ch = '-';
    }else if(a->ch=='-'&&b->ch=='+'){
        free(sum);
        return sub(b,a);
    }else if(a->ch=='+'&&b->ch=='-'){
        free(sum);
        return sub(a,b);
    }else if(a->ch=='+'&&b->ch=='+'){
        sum->ch='+';
    }
    for (int i = 0; i < SIZE; ++i) {
        int temp = (int)(a->data[i]-'0')+(int)(b->data[i]-'0')+(int)(sum->data[i]-'0');
        sum->data[i] = temp%10+'0';
        sum->data[i+1] = temp/10+'0';
        if (i + 1 == SIZE) {
            break;
        }
    }
    sum->size = SIZE;
    while (sum->size!=0&&sum->data[--sum->size] == 0+'0');
    sum->size++;
    return sum;
}
int comp(BigInteger* a,BigInteger* b){
    if(a->size!=b->size){
        return a->size-b->size;
    }
    for (int i = 0; i < a->size; ++i) {
        if(a->data[i] != b->data[i]){
            return -(a->data[i] - b->data[i]);
        }
    }
    return 0;
}
BigInteger* sub(BigInteger* a,BigInteger* b){
    BigInteger *result = create("");
    if(a->ch=='-'&&b->ch=='+'){
        free(result);
        return add(b,a);
    }else if(a->ch=='+'&&b->ch=='-'){
        free(result);
        return add(a,b);
    }else{
        if(comp(a,b)<0){
            result->ch = '-';
            BigInteger* temp = a;
            a = b;
            b = temp;
        }else{
            result->ch = '+';
        }
    }
    printf("%d\n", comp(a, b));
    for (int i = 0; i < SIZE; ++i) {
        if (i + 1 == SIZE) {
            break;
        }
        int temp = 0;
        if((int)(a->data[i]-'0')-(int)(b->data[i]-'0')-(int)(result->data[i]-'0')>=0){
            temp = (int)(a->data[i]-'0')-(int)(b->data[i]-'0')-(int)(result->data[i]-'0');
        } else{
            temp = (int)(a->data[i]-'0')+10-(int)(b->data[i]-'0')-(int)(result->data[i]-'0');
            result->data[i+1] = '1';
        }
        result->data[i] = temp+'0';
    }
    result->size = SIZE;
    while (result->size!=0&&result->data[--result->size] == 0+'0');
    result->size++;
    return result;
}
void print(BigInteger* num){
    int pos = SIZE;
    while (--pos) {
        if (num->data[pos] != 0+'0') {
            break;
        }
    }
    if(num->ch == '-'){
        printf("-");
    }
    show(num,pos);
}

void show(BigInteger *num, int pos) {
    if (pos != -1) {
        printf("%c",num->data[pos]);
        show(num,pos-1);
    }else{
        printf("\n");
    }
}

BigInteger* mult(BigInteger*a ,BigInteger* b){//123456789*987654321
    BigInteger *result = create("");
    for (int i = 0; i < b->size; ++i) {
        for (int j = 0; j < a->size; ++j) {
            if(i+j+1 == SIZE){
                i = SIZE;
                break;
            }
            int temp = (int)(a->data[j]-'0')*(int)(b->data[i]-'0')+(int)(result->data[j+i]-'0');
            result->data[j+i] = temp%10+'0';
            result->data[j+i+1] = (temp/10+(result->data[j+i+1]-'0')+'0');
        }
    }
    result->size = SIZE;
    while (result->size!=0&&result->data[--result->size] == 0+'0');
    result->size++;
    return result;
}
