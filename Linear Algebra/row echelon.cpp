#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <stdexcept>

using namespace std;

void print_table(vector<vector<double>> vec){
    for (int i = 0; i < vec.size(); i++){
        for (int j = 0; j < vec[i].size(); j++){
            cout << vec[i][j] << " ";
        }
        cout << endl;
    }
}

vector<vector<double>> reduce(vector<vector<double>> matrix){
    int size = matrix.size();
    double ratio = 0;
    if (matrix.size() != matrix[0].size()){
        throw runtime_error("Matrix must be square");
    }
    for (int i = 0; i < size - 1; i++){
        for (int j = size - 1; j > i; j--){
            if (matrix[i][j] == 0){
                continue;
            }
            else{
                try{
                    if (matrix[j - i][i] == 0){
                        throw runtime_error("Division by Zero");
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
    return matrix;
}

int main(){
    vector<vector<double>> vec = {{1, 9}, {3, 4}};
    vector<vector<double>> matrix = reduce(vec);
    print_table(matrix);
    return 0;
}