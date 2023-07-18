/*
naive implementation of the karatsuba algorithm. efficiency can be increased 
by using lookup tables for powers of 10 and using strings instead of double
to int conversions
*/
#include <iostream>
#include <cstdio>
#include <cstdint>
#include <vector>
#include <cmath>
#include <algorithm>
#include <ctime>

#pragma gcc optimize("Ofast")

using namespace std;

void printVectorInt(vector<int64_t> v){
    printf("size: %d; [", v.size());
    for (int64_t i = 0; i < v.size() - 1; i++){
        printf("%lld,", v[i]);
    }
    printf("%lld]\n", v[v.size() - 1]);
}

int64_t length(int64_t a){
    return int64_t(log10(a) + 1);
}

int64_t karatsuba(int64_t a, int64_t b){
    if (max(length(a), length(b)) == 1){
        return a * b;
    }
    int64_t m = max(length(a), length(b)) >> 1;
    /*split integers at position m - if m = 3 splitting 1230 will result in w being 1 and x being 230 */
    int64_t w = a / pow(10, m);
    int64_t x = a % (int64_t)pow(10, m);
    int64_t y = b / pow(10, m);
    int64_t z = b % (int64_t)pow(10, m);
    /*divide and conquer*/
    int64_t z0 = karatsuba(x, z);
    int64_t z1 = karatsuba(w + x, y + z);
    int64_t z2 = karatsuba(w, y);
    return (z2 * pow(10, m << 1)) + ((z1 - z2 - z0) * pow(10, m)) + z0;
}

int main(){
    int64_t a = 22093342;
    int64_t b = 52039892;
    clock_t t = clock();
    printf("%lld\n", karatsuba(a, b));
    t = clock() - t;
    printf("Time taken: %f seconds \n", ((double)t)/CLOCKS_PER_SEC);
    return 0;
}