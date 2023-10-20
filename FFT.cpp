#include <iostream>
#include <cstdio>
#include <cmath>
#include <vector>
#include <complex>
#include <algorithm>
#pragma GCC optimize("Ofast")
#define PI 3.14159265358979323846264

using namespace std;

typedef long double ld;

void print_vector(vector<complex<ld>> v){
    cout << "size: " << v.size() << "; [";
    for (int i = 0; i < v.size() - 1; i++){
        cout << v[i] << ", ";
    }
    cout << v[v.size() - 1] << "]" << endl;
}

void print_vector2(vector<vector<ld>> v){
    cout << "size: " << v.size() << "; [";
    for (int i = 0; i < v.size() - 1; i++){
        cout << "(" << v[i][0] << ", " << v[i][1] << "), ";
    }
    cout << "(" << v[v.size() - 1][0] << ", " << v[v.size() - 1][1] << ")" << "]" << endl;
}

void FFTUtil(vector<complex<ld>>& vec){
    int n = vec.size();
    if (n == 1){
        return;
    }
    complex<ld> root;
    root.real(cos(2 * PI / n));
    root.imag(sin(2 * PI / n));
    //evaluate primitive root of unity
    vector<complex<ld>> even; //following the Cooley-Tukey recursive FFT
    vector<complex<ld>> odd; //split into even and odd cases, compute DFT, combine
    for (int i = 0; i < n; i += 2){
        even.push_back(vec[i]);
    }
    for (int i = 1; i < n; i += 2){
        odd.push_back(vec[i]);
    }
    FFTUtil(even);
    FFTUtil(odd);
    for (int i = 0; i < n / 2; i++){
        vec[i] = even[i] + pow(root, i) * odd[i];
        vec[i + n / 2] = even[i] - pow(root, i) * odd[i];
    }
}

void FFT(vector<complex<ld>>& vec){
    int n = vec.size();
    FFTUtil(vec);
    for (int i = 0; i < n; i++){
        vec[i] = conj(vec[i]);
    }
}

void IFFT(vector<complex<ld>>& vec){
    int n = vec.size();
    if (n == 1){
        return;
    }
    FFTUtil(vec);
    for (int i = 0; i < n; i++){
        vec[i] = conj(vec[i]);
        vec[i] /= n; //relative scaling to achieve orignal array
    }
}


int main(){
    vector<complex<ld>> vec;
    for (ld i = -4*PI; i < 4*PI; i+=0.1){
        vec.push_back(complex<ld>(sinl(i), 0));
    }
    FFT(vec);
    print_vector(vec);
    return 0;
}