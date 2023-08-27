#include <iostream>
#include <vector>
#pragma GCC optimize("Ofast")

using namespace std;

/*
program to generate the Cayley table for the multiplicative group of integers mod n = U(n) where x in U(n) iff gcd(x, n) = 1 
(coprime) and n > x.
*/

void print_table(vector<vector<int>> vec){
    for (int i = 0; i < vec.size(); i++){
        for (int j = 0; j < vec[i].size(); j++){
            cout << vec[i][j] << " ";
        }
        cout << endl;
    }
}

void print_vec(vector<int> vec){
    for (int i = 0; i < vec.size(); i++){
        cout << vec[i] << " ";
    }
    cout << endl;
}

int gcd(int a, int b){
    if (b == 0){
        return a;
    }
    return gcd(b, a % b); //via the euclidean algorithm
}

vector<int> intgrpmodn(int n){
    vector<int> group;
    for (int i = 1; i < n; i++){
        if (gcd(i, n) == 1){
            group.push_back(i);
        }
    }
    return group;
}

vector<vector<int>> cayley_intgrpmodn(int n){
    vector<int> group;
    for (int i = 1; i < n; i++){
        if (gcd(i, n) == 1){
            group.push_back(i);
        }
    }
    vector<vector<int>> table(group.size() , vector<int>(group.size()));
    /*
        The multiplicative group of integers mod n is Abelian, meaning that the Cayley table (as a matrix) is symmetric - A^T=A
        Instead of iterating with j = 0 and table[i][j] = prod, start j at i and use table[i][j] = prod; table[j][i] = prod; to
        compute prod once. The naive approach is O(n^2), this approach is O(n*logn)
    */
    for (int i = 0; i < group.size(); i++){
        for (int j = i; j < group.size(); j++){
            int prod = (group[i] * group[j]) % n;
            table[i][j] = prod;
            table[j][i] = prod; 
        }
    }
    return table;
}

int main(){
    int mod = 8;
    vector<int> group = intgrpmodn(mod);
    vector<vector<int>> table = cayley_intgrpmodn(mod);
    print_table(table);
    return 0;
}