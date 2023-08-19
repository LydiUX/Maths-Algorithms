#include <cstdio>
#include <iostream>
#pragma GCC optimize("Ofast")

using namespace std;

/*
quicksort: 
-partitioning-
1. pick a random pivot element and swap it with the max element
2. a pointer is set at the beginning of the array (if the pointer > pivot). 
3. compare the elements after the pointer with the pivot until you find one smaller than (or equal to) the pivot. swap the element with the pointer.
4. the pointer location in the array is incremented by one; repeat step 3 until pointer location is pivot - 1.
5. the pivot is swapped with the pointer. the numbers to the pivot's left are smaller than it; the numbers on the right are bigger.
-quicksort-
6. two new arrays are created (left and right of the pivot (including pivot)) and sorted
    a. tail recursion is prefered
(7.) if the arrays are small enough (8 entries), use insertion sort.
*/

void printArray(int arr[], int n){
    printf("size: %d; [", n);
    for (int i = 0; i < n - 1; i++){
        printf("%d,", arr[i]);
    }
    printf("%d]\n", arr[n - 1]);
}

void insertionSort(int arr[], int min, int max){
    //i = min + 1; skip first as already in "sorted" array
    for (int i = min + 1; i <= max; i++){
        int data = arr[i];
        int index = i;
        while(index > min && arr[index - 1] > data){
            arr[index] = arr[index - 1];
            index--;
        }
        arr[index] = data;
    }
}

int partition(int arr[], int min, int max){
    swap(arr[rand() % (max - 1) + min], arr[max]);
    int pivot = arr[max];
    int pointer = min;
    for(int j = min; j < max; j++){
        if(arr[j] <= pivot){
            swap(arr[j], arr[pointer]);
            pointer++;
        }
    }
    swap(arr[pointer], arr[max]);
    return pointer;
}

void quicksort(int arr[], int min, int max){
    while(max > min){
        if (8 >= max - min){
            insertionSort(arr, min, max);
            break;
        }
        int pivot = partition(arr, min, max);
        if(max - pivot > pivot - min){
            quicksort(arr, min, pivot - 1);
            min = pivot + 1;
        }
        else{
            quicksort(arr, pivot + 1, max);
            max = pivot - 1;
        }
    }
}

int main(){
    int arr[] = { 1, 5, 9, 3, 4, -2, 7, 12, 41, 29, 38, 48, 57, 38, 12, 17};
    int max = sizeof(arr) / sizeof(arr[0]);
    int min = 0;
    quicksort(arr, min, max - 1);
    printArray(arr, max);
    return 0;
}