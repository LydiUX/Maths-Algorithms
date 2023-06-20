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

print(numericalIntegrate(lambda x: x, 5, 10, 20))