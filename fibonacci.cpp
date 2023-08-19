#include <stdio.h>
#include <stdlib.h>

int* fibonacci(int n){
    int* sequence = (int*)malloc((n) * sizeof(int));
    sequence[0] = 1;
    sequence[1] = 1;
    for (int i = 2; i < n; i++){
        sequence[i] = sequence[i - 1] + sequence[i - 2];
    }
    return sequence;
}

int main(){
    int n = 45;
    int* fib = fibonacci(n);
    if (n < 46){
        for (int i = 0; i < n; i++){
            printf("%d: %d\n", i + 1, fib[i]);
        }
    }
    else{
        free(fib);
        printf("Integer overflow, use n < 46\n");
        return 0;
    }
    free(fib);
    return 0;
}