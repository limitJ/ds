#include "biginteger.h"
#include <math.h>
#include <stdlib.h>
#define len(arr) sizeof(arr)/sizeof(arr[0])
int main() {
#include<stdio.h>

    BigInteger *a = create("123456789");
    BigInteger *b = create("9876543211");
    BigInteger *res = sub(a, b);
    print(res);
    BigInteger *e = create("123456789");
    BigInteger *f = create("987654321");
    BigInteger *g = mult(e, f);
    print(g);
    return 0;
}