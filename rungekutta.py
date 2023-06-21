#runge-kutta fourth-order numerical integrater

import math

class rungekutta:
    def __init__(self, steps):
        self.steps = steps
    
    def rungekutta(self, func, initx, inity, evaluatedx):
        h = (evaluatedx - initx) / self.steps
        for _ in range(self.steps):
            k1 = h * func(initx, inity)
            k2 = h * func(initx + 0.5 * h, inity + 0.5 * k1)
            k3 = h * func(initx + 0.5 * h, inity + 0.5 * k2)
            k4 = h * func(initx + h, inity + k3)
            evaluatedy = inity + (1/6)*(k1 + 2*k2 + 2*k3 + k4)
            inity = evaluatedy
            initx += h
        return evaluatedy

    def numericalIntegrate(self, func, xi, xf):
        initx = 0
        inity = func(initx)
        return self.rungekutta(lambda x,y: func(x), initx, inity, xf) - self.rungekutta(lambda x,y: func(x), initx, inity, xi)

    def polynomialIntegrate(self, xi, xf, *args):
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
        return self.rungekutta(lambda x,y: func(x), initx, inity, xf) - self.rungekutta(lambda x,y: func(x), initx, inity, xi)
    
#tests
integrater = rungekutta(steps=100)
print(integrater.rungekutta(lambda x,y: x**2+y, 4, 6, 10)) #solution to dy/dx=x^2+y(x) with initial condition y(4)=6 at x=10
print(integrater.numericalIntegrate(lambda x: math.sin(x), 5, 10)) #definite integral of sin(x) from x=5 to x=10
print(integrater.polynomialIntegrate(5,10,2,4,3,6)) #definite integral of 2x^3+4x^2+3x+6 from x=5 to x=10
