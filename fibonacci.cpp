#include <iostream>
#include <cstdio>
#include <vector>
#include <ctime>

using namespace std;

void generate(vector<int>& vec, int iter){
    if (iter <= 0){
        return;
    }
    switch (iter){
        case 1: 
            vec.push_back(1);
            break;
        case 2:
            vec.push_back(1);
            vec.push_back(1);
            break;
        default:
            vec.push_back(1);
            vec.push_back(1);
            for (int i = 1; i < iter; ++i){
                vec.push_back(vec[i - 1] + vec[i]);
            }
            break;
    }
}

int main(){
    clock_t t;
    t = clock();
    vector<int> vec;
    generate(vec, 10);
    t = clock() - t;
    printf("Time taken: %f seconds \n", ((double)t)/CLOCKS_PER_SEC);
    for (int i = 0; i < vec.size(); ++i){
        cout << vec[i] << endl;
    }
    return 0;
}