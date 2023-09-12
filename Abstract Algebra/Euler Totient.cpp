#include <cstdio>
#include <iostream>

using namespace std;

int gcd(int a, int b){
    if (b == 0){
        return a;
    }
    return gcd(b, a % b);
}

int totient(int n){
    int count = 0;
    for (int i = 2; i < n; i++){
        if (gcd(i, n) == 1){
            count++;
        }
    }
    return count;
}

int numCyclicSubgroup(int n){
    return totient(n);
}

int main(){
    printf("%d", totient(4));
    return 0;
}