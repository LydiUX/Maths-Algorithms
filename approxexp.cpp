#include <iostream>
#include <cstdio>
#include <vector>
#include <cmath>
#include <ctime>

//works best for small x (x <= 5)
//faster than cmath O(exp(n)) function, achieved using a taylor series

using namespace std;

int64_t factorial(int64_t a){
    int64_t ans = 1;
    for (int64_t i = a; i > 0; i--){
        ans *= i;
    }
    return ans;
}

long double taylorExp(long double x, int precision){
    if (precision > 20){
        precision = 20;
    }
    long double ans = 0;
    for (int64_t i = 0; i < precision; i++){
        ans += pow(x, i) / factorial(i);
    }
    return ans;
}

int main(){
    long double x = 10;
    clock_t t;
    t = clock();
    printf("%lf\n", exp(x));
    t = clock() - t;
    printf("Time taken: %f seconds \n", ((double)t)/CLOCKS_PER_SEC);
    t = clock();
    printf("%lf\n", taylorExp(x, 22));
    t = clock() - t;
    printf("Time taken: %f seconds \n", ((double)t)/CLOCKS_PER_SEC);
    return 0;
}