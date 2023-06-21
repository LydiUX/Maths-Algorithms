//runge-kutta fourth-order numerical integrater

#include <stdio.h>
#include <math.h>

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

double numericalIntegrate(double (*f)(double, double), double xi, double xf, int steps){
    double initx = 0.0;
    double inity = (*f)(initx, 0);
    return rungekutta((*f), &initx, &inity, xf, steps) - rungekutta((*f), &initx, &inity, xi, steps);
}

//test functions
double function(double x, double y){
    return pow(x,4) + y;
}

double function2(double x, double y){
    return cos(x); //do not use the y parameter here - the numerical integrater is for one variable only.
}

int main(){
    double initx = 0;
    double inity = 0;
    printf("%lf\n", rungekutta(function, &initx, &inity, 5, 20)); //solution to dy/dx=x^4+y(x) with y(0)=0 at x=5
    printf("%lf\n", numericalIntegrate(function2, 0, 10, 20)); //integral of f(x)=cos(x) from x=0 to x=10
    return 0;
}
