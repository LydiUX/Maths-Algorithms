#include <cstdio>
#include <iostream>
#include <ctime>
#pragma GCC optimize("Ofast")

using namespace std;

/*
quicksort: 
-partitioning-
1. pick a random pivot element and swap it with the last element in array
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
    swap(arr[rand() % (max - min + 1) + min], arr[max]);
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
    int max = sizeof(arr) / sizeof(arr[0]);
    clock_t t = clock();
    quicksort(arr, 0, max - 1); //max - 1 as arr[max] is out of index (starts at index 0)
    t = clock() - t;
    printf("Time taken: %f seconds\nArray:\n", ((double)t)/CLOCKS_PER_SEC);
    printArray(arr, max);
    return 0;
}