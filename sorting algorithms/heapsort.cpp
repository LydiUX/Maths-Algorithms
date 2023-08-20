#include <cstdio>
#include <iostream>
#include <ctime>
#pragma GCC optimize("Ofast")

using namespace std;

/*
heap sort:
1. build a binary tree from the given array
2. convert to max heap
3. swap the root (max) in the heap with the last element
4. remove the root - copy to input array
5. convert to max heap; repeat until all elements sorted and removed
6. reverse the order of the input array
*/

void printArray(int arr[], int n){
    printf("size: %d; [", n);
    for (int i = 0; i < n - 1; i++){
        printf("%d,", arr[i]);
    }
    printf("%d]\n", arr[n - 1]);
}

void heapify(int arr[], int n, int rootNode){
    int max = rootNode; //set maximum value in tree to the root node
    int leftChild = 2 * rootNode + 1;
    int rightChild = 2 * rootNode + 2; //location of children for implicit data structure (binary tree) in array
    if(arr[leftChild] > arr[max] && n > leftChild){
        max = leftChild;
    }
    if(arr[rightChild] > arr[max] && n > rightChild){
        max = rightChild;
    }
    if (rootNode != max){
        swap(arr[max], arr[rootNode]); //swap the rootNode with the maximum value so it's always the root node
        heapify(arr, n, max); //recurse so the entire tree reaches max heap
    }
}

void heapSort(int arr[], int n){
    for(int i = n / 2; i >= 0; i--){
        heapify(arr, n, i); //max heap - iterate backwards to traverse
    }
    for(int i = n; i >= 0; i--){
        swap(arr[0], arr[i]); //swap the value in index 0 with the sorted in index i
        heapify(arr, i, 0); //start with root 0 to get max value as the root node. i is decreasing as each iteration removes one value
    }
}

int main(){
    int arr[] = {
    -987, 764, 382, -531, -237, -468, -865, 932, -555, -723,
    -334, 440, -580, -998, 419, 280, -101, 719, 631, -996,
    -648, 945, -790, 447, -862, 542, -809, -743, 201, 658,
    684, -883, 837, -977, 906, -584, 275, -786, 69, -382,
    413, -37, -999, -221, -394, -505, 757, -30, 785, -866,
    771, -155, -499, -471, -944, 671, -902, 816, 509, -35,
    977, 217, 516, -911, 630, -797, 695, -442, 863, 876,
    -961, -864, 445, -566, 719, 461, -340, 156, 759, 488,
    -789, 513, 482, -377, 676, -156, -442, -378, -853, 366,
    657, -418, 582, 903, -239, -759, 926, 815, 726, -699,
    -243, 262, 3, 928, -586, -448, 535, 998, -12, -773,
    978, -475, -904, -690, -914, -401, -931, -599, -986, 190,
    419, -191, -253, -961, -567, -332, -611, 193, -630, -857,
    924, 590, 255, -891, 951, -828, -666, 994, -445, -695,
    665, -173, 71, -122, -328, 981, 905, -740, 268, -38,
    943, -952, -584, -171, -402, 862, 938, -731, -303, -621,
    796, -490, 431, -318, 755, -273, 184, 977, 77, -957,
    -836, -336, -572, 526, -928, -913, -894, -801, 413, -417,
    -666, -262, -581, -319, -693, -532, -969, 370, 650, -558,
    -466, 242, 812, 464, -566, -737, 732, -314, 949, -468,
    -39, -447, -92, 955, 238, -117, -773, 986, -276, 879,
    472, 609, -948, 544, 897, 705, -931, 672, 747, -987,
    -605, 835, -597, 990, -950, 742, 404, -344, 590, 464,
    -423, -654, 354, -996, 827, -352, 197, -154, 34, -11,
    -62, 434, -504, 285, 41, 906, -373, 734, -51, 906
    };
    int n = sizeof(arr) / sizeof(arr[0]);
    clock_t t = clock();
    heapSort(arr, n - 1); //n - 1 as arr[n] is out of index (starts at index 0)
    t = clock() - t;
    printf("Time taken: %f seconds\nArray:\n", ((double)t)/CLOCKS_PER_SEC);
    printArray(arr, n);
    return 0;
}