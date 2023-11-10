#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <stdexcept>

#pragma GCC optimize("Ofast")

typedef long double ld;

using namespace std;

void print_table(vector<vector<ld>> vec){
    for (int i = 0; i < vec.size(); i++){
        for (int j = 0; j < vec[i].size(); j++){
            cout << vec[i][j] << " ";
        }
        cout << endl;
    }
}

void reduce(vector<vector<ld>>& matrix){
    int size = matrix.size();
    ld ratio = 0;
    if (matrix.size() != matrix[0].size()){
        throw runtime_error("Matrix must be square\n");
    }
    for (int i = 0; i < size - 1; i++){
        for (int j = size - 1; j > i; j--){
            if (matrix[i][j] == 0){
                continue;
            }
            else{
                try{
                    if (matrix[j - i][i] == 0){
                        throw runtime_error("Division by Zero\n");
                    }
                    ratio = matrix[j][i] / matrix[j - 1][i];
                }
                catch (runtime_error& except){
                    for (int k = 0; k < size; k++){
                        swap(matrix[j][k], matrix[j - 1][k]);
                    }
                    continue;
                }
                for (int l = 0; l < size; l++){
                    matrix[j][l] = matrix[j][l] - ratio * matrix[j - 1][l]; //gaussian elimination
                }
            }
        }
    }
}

ld det(vector<vector<ld>>& matrix){
    reduce(matrix);
    int n = matrix.size();
    ld res = 1;
    for (int i = 0; i < n; ++i){
        res *= matrix[i][i];
    }
    return res;
}


int main(){
    vector<vector<ld>> vec = {{1, 9}, {3, 4}};
    det(vec);
    print_table(vec);
    return 0;
}