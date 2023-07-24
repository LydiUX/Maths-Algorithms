//runge-kutta numerical integrator

#include <iostream>
#include <cstdio>
#include <cmath>
#include <vector>
#include <cstdint>

#pragma gcc optimize("Ofast")

using namespace std;

typedef long double ld;

ld rungekutta4(ld (*f)(ld, ld), ld initx, ld inity, ld evaluatedx, int64_t steps){
    //ld initx = initxInp;
    //ld inity = inityInp;
    ld h = (evaluatedx - initx) / steps;
    ld evaluatedy;
    for (int64_t i = 0; i < steps; i++){
        ld k1 = h * (*f)(initx, inity);
        ld k2 = h * (*f)(initx + 0.5 * h, inity + 0.5 * k1);
        ld k3 = h * (*f)(initx + 0.5 * h, inity + 0.5 * k2);
        ld k4 = h * (*f)(initx + h, inity + k3);
        evaluatedy = inity + (1 / 6.0) * (k1 + 2 * k2 + 2 * k3 + k4);
        inity = evaluatedy;
        initx += h;
    }
    return evaluatedy;
}

ld numericalIntegrate(ld (*f)(ld, ld), ld xi, ld xf, int64_t steps){
    ld initx = 0.0;
    ld inity = (*f)(initx, 0);
    return rungekutta4((*f), initx, inity, xf, steps) - rungekutta4((*f), initx, inity, xi, steps);
}

ld func(ld x, ld y){
    return cos(x);
}

int main(){
    printf("%lf\n", numericalIntegrate(func, 0, 10, 20));
    return 0;
}