#numerical integrators

import math

class RKIntegrators(type): #metaclass for Runge-Kutta integrators
    def __new__(cls, name, bases, attrs): 
        #common attributes shared amongst subclasses
        attrs['evaluate'] = cls.evaluate
        attrs['numericalIntegrate'] = cls.numericalIntegrate
        attrs['polynomialIntegrate'] = cls.polynomialIntegrate
        return super().__new__(cls, name, bases, attrs)
    
    def evaluate(self, func, initx, inity, evaluatedx): #the actual work the integrators are doing
        h = (evaluatedx - initx) / self.steps
        for _ in range(self.steps):
            evaluatedy = inity + self.approximate(func, initx, inity, h)
            inity = evaluatedy
            initx += h
        return evaluatedy
    
    def approximate(self, func, initx, inity, h): #the method of approximation (slopes at different parts of an interval) changes between the integrators
        raise NotImplementedError 

    def numericalIntegrate(self, func, xi, xf): #numerical integration in 1D
        initx = 0
        inity = func(initx)
        return self.evaluate(lambda x, y: func(x), initx, inity, xf) - self.evaluate(lambda x, y: func(x), initx, inity, xi)
    
    def polynomialIntegrate(self, xi, xf, *args): #polynomial integration in 1D
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
        return self.evaluate(lambda x, y: func(x), initx, inity, xf) - self.evaluate(lambda x, y: func(x), initx, inity, xi)

class rungekutta1(metaclass = RKIntegrators): #(first-order Runge-Kutta, aka Euler's method)
    def __init__(self, steps):
        self.steps = steps
    
    def approximate(self, func, initx, inity, h):
        return h * func(initx, inity) #just one slope approximating the interval  

class rungekutta2(metaclass = RKIntegrators): #(second-order Runge-Kutta)
    def __init__(self, steps):
        self.steps = steps
        
    def approximate(self, func, initx, inity, h):
        k1 = func(initx, inity)
        k2 = func(initx + h, inity + h * k1)
        return (h/2) * (k1 + k2)

class rungekutta3(metaclass = RKIntegrators): #(third-order Runge-Kutta)
    def __init__(self, steps):
        self.steps = steps
        
    def approximate(self, func, initx, inity, h):
        k1 = func(initx, inity)
        k2 = func(initx + 0.5 * h, inity + 0.5 * k1 * h)
        k3 = func(initx + h, inity - h * k1 + 2 * h * k2)
        return (h/6) * (k1 + 4*k2 + k3)

class rungekutta4(metaclass = RKIntegrators): #(fourth-order Runge-Kutta)
    def __init__(self, steps):
        self.steps = steps
    
    def approximate(self, func, initx, inity, h):
        k1 = func(initx, inity) #slope at first part of the interval
        k2 = func(initx + 0.5 * h, inity + 0.5 * k1 * h) #slope at the midpoint using k1
        k3 = func(initx + 0.5 * h, inity + 0.5 * k2 * h) #slope at the midpoint using k2
        k4 = func(initx + h, inity + k3 * h) #slope at the end of the interval
        return (h/6) * (k1 + 2*k2 + 2*k3 + k4) #weighted average towards midpoint

#tests
integrator1 = rungekutta1(steps=100)
print(integrator1.evaluate(lambda x,y: x**2+y, 4, 6, 10)) #solution to dy/dx=x^2+y(x) with initial condition y(4)=6 at x=10
print(integrator1.numericalIntegrate(lambda x: math.sin(x), 5, 10)) #definite integral of sin(x) from x=5 to x=10
print(integrator1.polynomialIntegrate(5,10,2,4,3,6)) #definite integral of 2x^3+4x^2+3x+6 from x=5 to x=10
integrator2 = rungekutta2(steps=100)
print(integrator2.evaluate(lambda x,y: x**2+y, 4, 6, 10)) #solution to dy/dx=x^2+y(x) with initial condition y(4)=6 at x=10
print(integrator2.numericalIntegrate(lambda x: math.sin(x), 5, 10)) #definite integral of sin(x) from x=5 to x=10
print(integrator2.polynomialIntegrate(5,10,2,4,3,6)) #definite integral of 2x^3+4x^2+3x+6 from x=5 to x=10
integrator3 = rungekutta3(steps=100)
print(integrator3.evaluate(lambda x,y: x**2+y, 4, 6, 10)) #solution to dy/dx=x^2+y(x) with initial condition y(4)=6 at x=10
print(integrator3.numericalIntegrate(lambda x: math.sin(x), 5, 10)) #definite integral of sin(x) from x=5 to x=10
print(integrator3.polynomialIntegrate(5,10,2,4,3,6)) #definite integral of 2x^3+4x^2+3x+6 from x=5 to x=10
integrator4 = rungekutta4(steps=100)
print(integrator4.evaluate(lambda x,y: x**2+y, 4, 6, 10)) #solution to dy/dx=x^2+y(x) with initial condition y(4)=6 at x=10
print(integrator4.numericalIntegrate(lambda x: math.sin(x), 5, 10)) #definite integral of sin(x) from x=5 to x=10
print(integrator4.polynomialIntegrate(5,10,2,4,3,6)) #definite integral of 2x^3+4x^2+3x+6 from x=5 to x=10