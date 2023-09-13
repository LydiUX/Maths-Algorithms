#include <iostream>
#include <cstdio>
#include <cmath>
#include <vector>
#include <complex>
#pragma GCC optimize("Ofast")
#define PI 3.14159265358979323846264

using namespace std;

typedef long double ld;

void printVector(vector<complex<ld>> v){
    cout << "size: " << v.size() << "; [";
    for (int i = 0; i < v.size() - 1; i++){
        cout << v[i] << ", ";
    }
    cout << v[v.size() - 1] << "]" << endl;
}

void FFT(vector<complex<ld>>& vec){
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
    FFT(even);
    FFT(odd);
    for (int i = 0; i < n / 2; i++){
        vec[i] = even[i] + pow(root, i) * odd[i];
        vec[i + n / 2] = even[i] - pow(root, i) * odd[i];
    }
}

void IFFT(vector<complex<ld>>& vec){
    int n = vec.size();
    if (n == 1){
        return;
    }
    for (int i = 0; i < n; i++){
        vec[i] = conj(vec[i]); //can apply same FFT alg if original dataset has been changed to conjugate form
    }
    FFT(vec);
    for (int i = 0; i < n; i++){
        vec[i] = conj(vec[i]);
        vec[i] /= n; //relative scaling to achieve orignal array
    }
}

int main(){
    vector<complex<ld>> vec = {complex<ld>(1, 0), complex<ld>(2, 0), complex<ld>(3, 0), complex<ld>(9, 0)};
    FFT(vec);
    IFFT(vec);
    printVector(vec);
    return 0;
}