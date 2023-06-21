#polynomial derivatives

def polynomialDerivative(format, *args):
    coefList = []
    for coefs in args:
        coefList.append(coefs)
    for i in range(len(coefList)):
        coefList[i] *= len(coefList) - i - 1
    coefList = coefList[-1:] + coefList[:-1]
    coefList.pop(0)
    if format == 'l':
        return coefList
    elif format == 'f':
        def polynomial(x):
            sum = 0
            for i in range(len(coefList)):
                sum += coefList[i] * x ** (len(coefList) - i - 1)
            return sum
        return polynomial
    elif format == 'p':
        coefListStr = [str(i) for i in coefList]
        for i in range(len(coefList)):
            if (len(coefListStr) - i - 1) != 0:
                coefListStr[i] = coefListStr[i] + "*x^" + str((len(coefListStr) - i - 1)) + "+"
        return 'P\'(x)=' + ''.join(coefListStr)
    else:
        return
    
def evaluatePolynomial(func, evalpoint):
    try:
        return func(evalpoint)
    except:
        raise TypeError

print(polynomialDerivative('p', 9,4,3,2))
print(evaluatePolynomial(polynomialDerivative('s', 9,4,3,2), 4))