#include <iostream>
#include <ctime>
#include <cmath>
#include <stdexcept>
#include <functional>

using namespace std;

#pragma GCC optimize("Ofast", "unroll-loops")

class Newton {
    private:
        int iter;
        function<double(double)> func;

    public:
        Newton(int iter, function<double(double)> func) : iter(iter), func(func) {};

        double derivative(double eval) {
            return 0.5 * (1 / 0.0001) * (func(eval + 0.0001) - func(eval - 0.0001));
        }

        double newton(double guess) {
            double y = guess;
            for (int i = 0; i < iter; ++i) {
                if (y - (y - func(y) / derivative(y)) > 0.001) {
                    y = y - func(y) / derivative(y);
                }
                else {
                    return y;
                }
            }
            throw invalid_argument("did not converge");
        }
};

int main() {
    Newton N(1000, [](double x){ return x * x - 1; });
    cout << N.newton(3) << endl;
    return 0;
}