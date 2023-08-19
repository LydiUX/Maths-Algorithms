#include <cstdio>
#include <iostream>
#include <ctime>
#include <cstring>
#pragma GCC optimize("Ofast")

using namespace std;

/*
counting sort:
1. find max element in an array and initialise aux array with max + 1 length
2. in the original array count the appearances of each element and store the count in the aux array (each position of the 
aux array for each number in the original array)
3. for each element in the aux array, set it to the cumulative sum of the previous elements before and including that element.
this will be the new "count" of the number
4. traverse the original array and find the position of the element in the aux array. subtract the count of said element
in the aux array with the position of the element in the original array - this is the output index. insert the element in the 
output array in index output index.
5. decrease the count of that element by 1
6. copy the output array to the original array
*/

void printArray(int arr[], int n){
    printf("size: %d; [", n);
    for (int i = 0; i < n - 1; i++){
        printf("%d,", arr[i]);
    }
    printf("%d]\n", arr[n - 1]);
}

void countingSort(int arr[], int n){
    int max = arr[0];
    for(int i = 0; i <= n; i++){
        if(arr[i] > max){
            max = arr[i];
        }
    }
    int aux[max + 1], ret[n];
    memset(aux, 0, sizeof(aux));
    for(int i = 0; i <= n; i++){
        aux[arr[i]]++;
    }
    for(int i = 0; i <= max; i++){
        aux[i] += aux[i - 1];
    }
    for(int i = 0; i <= n; i++){
        ret[aux[arr[i]] - 1] = arr[i];
        aux[arr[i]]--;
    }
    for(int i = 0; i <= n; i++){
        arr[i] = ret[i];
    }
}

int main(){
    int arr[] = {267,263,58,47,148,206,241,261,267,24,275,250,237,102,83,35,157,274,9,219,115,294,89,233,156,194,173,27,43,82,215,259,45,222,255,142,127,196,51,93,169,25,292,105,76,24,90,233,247,99,101,61,42,190,295,198,32,116,225,24,198,139,284,243,10,187,33,137,31,84,180,150,58,171,255,135,144,294,16,91,42,66,152,84,256,95,231,289,211,155,12,109,243,245,0,253,81,34,39,112,67,168,262,126,288,166,210,132,108,175,223,99,242,23,132,146,119,62,83,29,166,45,87,109,290,88,10,19,71,299,81,87,166,292,162,154,106,71,235,215,196,157,263,137,129,95,283,248,157,66,227,23,60,263,81,299,300,40,18,70,39,99,107,154,90,269,7,146,40,191,60,185,297,22,21,126,66,253,73,224,268,249,196,27,212,226,26,211,266,44,231,4,92,37,108,131,5,115,277,295,6,286,179,2,258,149,77,23,102,100,196,18,48,40,46,209,266,21,69,232,14,300,185,106,286,293,186,240,57,112,235,12,46,62,264,253,161,41,277,212,141,121,230,138,162,225,47,76,246,116,7,260,64,142,14,49,134,150,289,140,262,172,152,257,184,65,210,44,106,135,205,196,256,134,33,66,59,29,143,254,145,99,214,158,241,177,207,75,26,145,164,237,266,16,194,149,81,52,142,136};
    int n = sizeof(arr) / sizeof(arr[0]);
    clock_t t = clock();
    countingSort(arr, n - 1); //n - 1 as arr[n] is out of index (starts at index 0)
    t = clock() - t;
    printf("Time taken: %f seconds\nArray:\n", ((double)t)/CLOCKS_PER_SEC);
    printArray(arr, n);
    return 0;
}