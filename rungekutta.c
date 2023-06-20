#include <stdio.h>

double function(double x, double y){
    return x + y;
}

double rungekutta(double (*f)(double, double), double* initx, double* inity, double evaluatedx, int steps){
    double h = (evaluatedx - *initx) / steps;
    double evaluatedy;
    for(int i = 0; i < steps; i++){
        double k1 = h * (*f)(*initx, *inity);
        double k2 = h * (*f)(*initx + 0.5 * h, *inity + 0.5 * k1);
        double k3 = h * (*f)(*initx + 0.5 * h, *inity + 0.5 * k2);
        double k4 = h * (*f)(*initx + h, *inity + k3);
        evaluatedy = *inity + (1/6.0)*(k1 + 2*k2 + 2*k3 + k4);
        *inity = evaluatedy;
        *initx += h;
    }
    return evaluatedy;
}

int main(){
    double initx = 0;
    double inity = 1;
    double evaluatedx = 1;
    int steps = 2;
    printf("The solution to dy/dx (%d steps) with y(%lf)=%lf is y(%lf)=%lf\n", steps, initx, inity, evaluatedx, rungekutta(function, &initx, &inity, evaluatedx, steps));
    return 0;
}
