#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <stdexcept>
#include <complex>
#include <fstream>

using namespace std;

typedef long double ld;
typedef complex<ld> cpx;

void print_vec(vector<cpx> v){
    cout << "size: " << v.size() << "; [";
    for (int i = 0; i < v.size() - 1; i++){
        cout << v[i] << ", ";
    }
    cout << v[v.size() - 1] << "]" << endl;
}

vector<cpx> mandelbrot_zoom(cpx c, int iter){
    vector<cpx> res;
    cpx temp = {0, 0};
    for (int i = 0; i < iter; ++i){
        temp = pow(temp, 2);
        temp += c;
        res.push_back(temp);
    }
    return res;
}

/*
a complex number c is within the mandelbrot set if and only if
|z_n| <= 2 (c does not cause the recursive z_{n+1}=z_n^2+c to explode to infinity)
*/

int mandelbrot_test(cpx c, cpx& temp, int& it){
    if (abs(temp) > pow(10, 8)){
        return 0;
    }
    if (it > pow(10, 4)){
        return 1;
    }
    temp = pow(temp, 2);
    temp += c;
    it++;
    return mandelbrot_test(c, temp, it);
}

vector<cpx> build_mandelbrot(ld max, ld increment){
    cpx test, temp;
    vector<cpx> res;
    int it;
    for (ld i = -max; i < max; i += increment){
        for (ld j = -max; j < max; j += increment){
            temp = {0, 0};
            it = 0;
            test = {i, j};
            cout << test << endl;
            if (mandelbrot_test(test, temp, it)){
                res.push_back(test);
            }
        }
    }
    return res;
}

int main(){
    ofstream output;
    output.open("output.txt");
    vector<cpx> set = build_mandelbrot(2, 0.01);
    /* for normal coordinate representation 
    for (int i = 0; i < set.size() - 1; i++){
        output << set[i] << ", ";
    }
    output << set[set.size() - 1];
    */

    /* for matplotlib + use with python script*/
    for (int i = 0; i < set.size(); i++){
        output << set[i].real() << "\n";
    }
    for (int i = 0; i < set.size() - 1; i++){
        output << set[i].imag() << "\n";
    }
    output << set[set.size() - 1].imag();
    output.close();
    return 0;   
}