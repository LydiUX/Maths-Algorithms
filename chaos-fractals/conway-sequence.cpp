#include <iostream>
#include <fstream>
#include <vector>

#pragma GCC optimize("Ofast")

using namespace std;

int main(){
    ofstream f;
    f.open("output.txt");
    vector<long double> v(3, 1);
    //wjat the fuck am I COOKING!!
    for (int i = 3; i < 2000; i++){
        v.push_back(v[v[i - 1]] + v[i - v[i - 1]]);
    }
    for (int i = 1; i < v.size(); i++){
        //f << (int)(v[i] - i / 2) << endl;
        //f << v[i] / i << endl;
        f << (int)v[i] << endl;
    }
    for (int i = 1; i < v.size(); i++){
        f << i << endl;
    }
    f.close();
    return 0;
}