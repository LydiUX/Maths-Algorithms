// logistic map x_n+1 = rx_n(1-x_n)

#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>

#pragma GCC optimize("Ofast,unroll-loops")

void lm_value(long double r, long double* x, int depth) {
    if (depth == 0) return;
    *x = r * (*x) * (1 - (*x));
    lm_value(r, x, depth - 1);
}

std::vector<std::vector<long double>> lm_plot(long double& r, int iter) {
    long double x;
    long double increment = powf(10, -floorf(log10(iter)));
    std::vector<std::vector<long double>> ret;
    for (int i = 0; i < iter; ++i) {
        x = 0.5;
        lm_value(r, &x, iter); // stabilise
        for (int j = 0; j < 100; ++j) {
            lm_value(r, &x, 1);
            ret.push_back({r, x}); // collect values
            std::cout << r << ", " << x << std::endl;
        }
        r += increment;
    }
    return ret;
}

int main(void) {
    std::ofstream f;
    long double r = -2;
    f.open("logistic.txt");
    std::vector<std::vector<long double>> container = lm_plot(r, 60000);
    for (auto& i : container) {
        f << i[0] << std::endl;
    }
    for (auto& j : container) {
        f << j[1] << std::endl;
    }
    return 0;
}