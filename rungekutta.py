#runge-kutta fourth-order numerical integrator

import math

def rungekutta(func, initx, inity, evaluatedx, steps):
    h = (evaluatedx - initx) / steps
    for _ in range(steps):
        k1 = h * func(initx, inity)
        k2 = h * func(initx + 0.5 * h, inity + 0.5 * k1)
        k3 = h * func(initx + 0.5 * h, inity + 0.5 * k2)
        k4 = h * func(initx + h, inity + k3)
        evaluatedy = inity + (1/6)*(k1 + 2*k2 + 2*k3 + k4)
        inity = evaluatedy
        initx += h
    return evaluatedy

def numericalIntegrate(func, xi, xf, steps):
    initx = 0
    inity = func(initx)
    return rungekutta(lambda x,y: func(x), initx, inity, xf, steps) - rungekutta(lambda x,y: func(x), initx, inity, xi, steps)

def polynomialIntegrate(xi, xf, steps, *args):
    polynomial = []
    for coefs in args:
        polynomial.append(coefs)
    def func(x):
        sum = 0
        for i in range(len(polynomial)):
            sum += polynomial[i] * x**(len(polynomial) - i - 1)
        return sum
    initx = 0
    inity = func(initx)
    return rungekutta(lambda x,y: func(x), initx, inity, xf, steps) - rungekutta(lambda x,y: func(x), initx, inity, xi, steps)
    
#tests
print(rungekutta(lambda x,y: x**2+y, 4, 6, 10, 100)) #solution to dy/dx=x^2+y(x) with initial condition y(4)=6 at x=10
print(polynomialIntegrate(5,10,100,2,4,3,6)) #definite integral of 2x^3+4x^2+3x+6 from x=5 to x=10
print(numericalIntegrate(lambda x: math.sin(x), 5, 10, 20)) #definite integral of sin(x) from x=5 to x=10