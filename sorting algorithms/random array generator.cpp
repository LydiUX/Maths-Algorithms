#include <cstdio>
#include <iostream>
#pragma GCC optimize("Ofast")

using namespace std;

void printArray(int arr[], int n){
    printf("size: %d; [", n);
    for (int i = 0; i < n - 1; i++){
        printf("%d,", arr[i]);
    }
    printf("%d]\n", arr[n - 1]);
}

void randomFillArray(int arr[], int n, int min, int max){
    for(int i = 0; i <= n; i++){
        arr[i] = rand() % (max - min + 1) + min;
    }
}

int main(){
    int size, min, max;
    printf("Size of array, minimum value, maximum value (32bit integer seperated by spaces):\n");
    scanf("%d %d %d", &size, &min, &max);
    int arr[size];
    int n = sizeof(arr) / sizeof(arr[0]);
    if(min > max){
        main();
    }
    randomFillArray(arr, n - 1, min, max);
    printArray(arr, n);
    return 0;
}