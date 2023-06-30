#include <stdio.h>
#include <math.h>
#include <time.h>

double func(double x){
    return pow(x, 4) + sin(2 * x) - 6;
}

double newton(double (*f)(double), double* initialGuess, int iterations){
    for (int i = 0; i < iterations; i++){
        /*
        For maximum accuracy, a central difference finite derivative is used to approximate f'(x).
        */
        double derivative = 0.5 * (1 / 0.000001) * ((*f)(*initialGuess + 0.000001) - (*f)(*initialGuess - 0.000001));
        /*
        If the derivative (which is in the denominator) is less than 0.000000000000001, break out of Newton's
        Method as lim(n->0+)(1/n) tends to infinity, losing accuracy. Choose a different initial guess to see 
        if it converges.
        */
        if (fabs(derivative) < 0.00000000000001){
            break;
        }
        double newGuess = *initialGuess - (*f)(*initialGuess) / derivative; 
        /*
        If the new guess is within the accepted tolerance (both initial guess and new guess settle on one
        value), return the new guess as the root of the function.
        */
        if (fabs(newGuess - *initialGuess) <= 0.00000001){
            return newGuess;
        }
        *initialGuess = newGuess; //update newton's method if the new guess is not within tolerance
    }
    printf("Newton's method failed to converge\n");
    return 0;
}

int main(){
    double initialGuess = 100;
    clock_t t = clock();
    printf("Newton's method converges to: %f\n", newton(func, &initialGuess, 1000));
    printf("Time taken: %f seconds \n", ((double)clock() - t)/CLOCKS_PER_SEC);
    return 0;
}