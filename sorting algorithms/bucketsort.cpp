#include <cstdio>
#include <iostream>
#include <ctime>
#include <algorithm>
#include <vector>
#pragma GCC optimize("Ofast")

using namespace std;

/*
bucket sort: (useful for sorting data between 0 - 1)
1. from an array of n elements, create n buckets (arrays)
2. for each element in the input array, multiply by length of the bucket array
3. for each element in the input array, the integer representation of the element is the index of which bucket it should be inserted into
4. insert the element into the respective bucket for all elements in the input array
5. sort the elements in each bucket using a stable sorting algorithm
6. insert elements from buckets into original array.
*/

void printArray(float arr[], int n){
    printf("size: %d; [", n);
    for (int i = 0; i < n - 1; i++){
        printf("%f,", arr[i]);
    }
    printf("%f]\n", arr[n - 1]);
}

void bucketSort(float arr[], int n){
    vector<float> bucket[n + 1]; //+1 buckets for the 0 bucket - n is the length which does not account for the one missing bucket
    for(int i = 0; i <= n; i++){
        bucket[int(arr[i] * n)].push_back(arr[i]);
    }
    for(int i = 0; i < n; i++){
        sort(bucket[i].begin(), bucket[i].end());
    }
    for(int i, index = 0; i < n; i++){
        for(int j = 0; j < bucket[i].size(); j++){
            arr[index++] = bucket[i][j];
        }
    }
}

int main(){
    float arr[] = {
    0.862386, 0.499441, 0.071135, 0.754256, 0.212342,
    0.328939, 0.884535, 0.634684, 0.965321, 0.106318,
    0.931067, 0.788589, 0.598309, 0.774050, 0.067513,
    0.370565, 0.171477, 0.735337, 0.938775, 0.601168,
    0.755702, 0.592834, 0.364220, 0.411761, 0.841647,
    0.933944, 0.161786, 0.897684, 0.912311, 0.787812,
    0.789363, 0.898026, 0.963383, 0.650068, 0.527289,
    0.642872, 0.575968, 0.481160, 0.488717, 0.823362,
    0.597598, 0.128388, 0.966324, 0.048498, 0.791390,
    0.990195, 0.333672, 0.635305, 0.377942, 0.143318,
    0.442199, 0.349591, 0.318934, 0.788888, 0.865616,
    0.232756, 0.260276, 0.767582, 0.256594, 0.236789,
    0.958662, 0.966492, 0.188890, 0.259146, 0.361325,
    0.786452, 0.481496, 0.032975, 0.373249, 0.711250,
    0.655846, 0.702461, 0.899971, 0.446363, 0.394249,
    0.388500, 0.877971, 0.394325, 0.282256, 0.048978,
    0.448914, 0.809455, 0.525279, 0.384705, 0.240680,
    0.929727, 0.901418, 0.153347, 0.895253, 0.290339,
    0.981215, 0.543484, 0.799008, 0.722497, 0.484679
    };  
    int n = sizeof(arr) / sizeof(arr[0]);
    clock_t t = clock();
    bucketSort(arr, n - 1); //n - 1 as arr[n] is out of index (starts at index 0)
    t = clock() - t;
    printf("Time taken: %f seconds\nArray:\n", ((double)t)/CLOCKS_PER_SEC);
    printArray(arr, n);
    return 0;
}