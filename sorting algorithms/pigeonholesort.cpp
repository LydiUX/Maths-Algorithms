#include <cstdio>
#include <iostream>
#include <ctime>
#include <vector>
#pragma GCC optimize("Ofast")

using namespace std;

/*
pigeonhole sort:
1. find the minimum and maximum values in the original array. find the range (max - min + 1)
2. initialise a pigeonhole array of empty pigeonholes with the array of length range. 
each index of the array is a pigeonhole (each pigeonhole is a vector)
3. traverse the original array and put values into its respective hole - value arr[i] -> hole[arr[i] - min]
4. loop the pigeonhole array and put the values in the pigeonholes back into the original array -
each index of the array should be hole[i][j]
*/

void printArray(int arr[], int n){
    printf("size: %d; [", n);
    for (int i = 0; i < n - 1; i++){
        printf("%d,", arr[i]);
    }
    printf("%d]\n", arr[n - 1]);
}

void pigeonholeSort(int arr[], int n){
    int min, max = arr[0];
    for(int i = 0; i <= n; i++){
        if(arr[i] > max){
            max = arr[i];
        }
        if(arr[i] < min){
            min = arr[i];
        }
    }
    vector<int> hole[max - min + 1];
    for(int i = 0; i <= n; i++){
        hole[arr[i] - min].push_back(arr[i]);
    }
    for(int i, index = 0; i <= max - min; i++){
        for(int j = 0; j < hole[i].size(); j++){
            arr[index++] = hole[i][j];
        }
    }
}

int main(){
    int arr[] = {267,263,58,47,148,206,241,261,267,24,275,250,237,102,83,35,157,274,9,219,115,294,89,233,156,194,173,27,43,82,215,259,45,222,255,142,127,196,51,93,169,25,292,105,76,24,90,233,247,99,101,61,42,190,295,198,32,116,225,24,198,139,284,243,10,187,33,137,31,84,180,150,58,171,255,135,144,294,16,91,42,66,152,84,256,95,231,289,211,155,12,109,243,245,0,253,81,34,39,112,67,168,262,126,288,166,210,132,108,175,223,99,242,23,132,146,119,62,83,29,166,45,87,109,290,88,10,19,71,299,81,87,166,292,162,154,106,71,235,215,196,157,263,137,129,95,283,248,157,66,227,23,60,263,81,299,300,40,18,70,39,99,107,154,90,269,7,146,40,191,60,185,297,22,21,126,66,253,73,224,268,249,196,27,212,226,26,211,266,44,231,4,92,37,108,131,5,115,277,295,6,286,179,2,258,149,77,23,102,100,196,18,48,40,46,209,266,21,69,232,14,300,185,106,286,293,186,240,57,112,235,12,46,62,264,253,161,41,277,212,141,121,230,138,162,225,47,76,246,116,7,260,64,142,14,49,134,150,289,140,262,172,152,257,184,65,210,44,106,135,205,196,256,134,33,66,59,29,143,254,145,99,214,158,241,177,207,75,26,145,164,237,266,16,194,149,81,52,142,136};
    int n = sizeof(arr) / sizeof(arr[0]);
    clock_t t = clock();
    pigeonholeSort(arr, n - 1); //n - 1 as arr[n] is out of index (starts at index 0)
    t = clock() - t;
    printf("Time taken: %f seconds\nArray:\n", ((double)t)/CLOCKS_PER_SEC);
    printArray(arr, n);
    return 0;
}