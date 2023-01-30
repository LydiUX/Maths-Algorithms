#Fast multiplication in under O(n^2)! However, does not work with huge integers (ironic, because this is the one that is a galactic algorithm)
#This is due to floating point rounding errors in the complex number module of the math library.
from decimal import *
import math

def ROOTS_OF_UNITY(root):
    return complex(math.cos(2*math.pi/root), math.sin(2*math.pi/root))
    
def FFT(polynomial): #Following the Cooley-Tukey Algorithm https://en.wikipedia.org/wiki/Cooley–Tukey_FFT_algorithm
    n = len(polynomial)
    if n == 1:
        return polynomial 
    w = ROOTS_OF_UNITY(n)
    evenPolynomial = polynomial[::2]
    oddPolynomial = polynomial[1::2]
    ansEven = FFT(evenPolynomial)
    ansOdd = FFT(oddPolynomial)
    ans = [0]*n
    for i in range(n//2):
        ans[i] = ansEven[i] + w**i*ansOdd[i]
        ans[i+n//2]=ansEven[i]-w**i*ansOdd[i]
    return ans

def IFFT(polynomial):
    def inverse(polynomial):
        n = len(polynomial)
        if n == 1:
            return polynomial
        w = ROOTS_OF_UNITY(-n)
        evenPolynomial = polynomial[::2]
        oddPolynomial = polynomial[1::2]
        ansEven = inverse(evenPolynomial)
        ansOdd = inverse(oddPolynomial)
        ans = [0]*n
        for i in range(n//2):
            ans[i] = ansEven[i] + w**i*ansOdd[i]
            ans[i+n//2]=ansEven[i]-w**i*ansOdd[i]
        return ans
    def fix(polynomial):
        for i in range(len(polynomial)):
            polynomial[i] *= 1/len(polynomial)
        return polynomial
    return fix(inverse(polynomial)) 

def INT_REAL_CONVOLVE(p1, p2): #this convolves the product of the two transforms, which gives the product
    n = len(p1)
    p1, p2 = FFT(p1), FFT(p2)
    convolved = IFFT([p1[i] * p2[i] for i in range(n)])
    return [round(convolved[i].real) for i in range(len(convolved))]

#code courtesy of https://github.com/Akashnil/fft-multiplication/blob/master/complex-arithmetic.py#L21
#I fixed some bugs and this now works; my approach would be the same. See https://www.cs.rug.nl/~ando/pdfs/Ando_Emerencia_multiplying_huge_integers_using_fourier_transforms_paper.pdf

def FFT_MULTIPLY(num1, num2):
    def MULTIPLY_COEFS(x, y):    
        n = 1 << (len(bin(max(len(x),len(y))-1))-1)
        x = x + [0] * (n - len(x))
        y = y + [0] * (n - len(y))
        z = INT_REAL_CONVOLVE(x, y)
        carry = 0
        non_zero = 0
        for i in range(len(z)):
            carry += z[i]
            z[i] = carry % 2
            if z[i] != 0:
                non_zero = i
            carry = carry / 2
        return z[:non_zero+1]
    num1Array = [int(digit) for digit in bin(num1)[:1:-1]]
    num2Array = [int(digit) for digit in bin(num2)[:1:-1]]
    answerArray = MULTIPLY_COEFS(num1Array, num2Array)
    ans = 0
    for bit in reversed(answerArray):
        ans = (ans << 1) | int(bit)
    return ans

assert(FFT_MULTIPLY(2,3)) == 6

print(FFT_MULTIPLY(3004,2003))