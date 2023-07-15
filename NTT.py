#number theoretic transform
import time

def modular_power(a, b, modulus):
    if a == 0:
        return 0 
    result = 1
    a %= modulus
    while b > 0:
        if b & 1 == 1:
            result *= a % modulus
        b >>= 1 #equivalent to b //= 2
        a *= a % modulus
    return result

def extended_gcd(a, b):
    if b == 0:
        return a, 1, 0
    gcd, x, y = extended_gcd(b, a % b)
    return gcd, y, x - (a // b) * y
    
def modular_inverse(a, modulus):
    gcd, x, _ = extended_gcd(a, modulus)
    if gcd != 1:
        raise ValueError #modular multiplicative inverse does not exist
    return x % modulus

def NTT(polynomial, size, generator, modulus): 
    '''
    size refers to the size of the polyonmial. The size of the polynomial is a power of 2; i.e. 2^k. Constraint: (size | modulus - 1).
    The maximum degree of the polynomial is n-1. 
    The generator is the primitive root of unity under the galois field F_modulus.
    '''
    if size == 1:
        return polynomial
    polynomial_even = polynomial[::2] #we use a divide and conquer approach
    polynomial_odd = polynomial[1::2]
    eval_point = generator**2 % modulus
    polynomial_even = NTT(polynomial_even, size // 2, eval_point, modulus)
    polynomial_odd = NTT(polynomial_odd, size // 2, eval_point, modulus)
    for i in range(size // 2):
        polynomial[i] = (polynomial_even[i] + generator**i * polynomial_odd[i]) % modulus
        polynomial[i + size // 2] = (polynomial_even[i] + generator**(i + size // 2) * polynomial_odd[i]) % modulus
    return polynomial

def INTT(polynomial, size, generator, modulus):
    if size == 1:
        return polynomial
    for i in range(1, (size + 1) // 2):
        polynomial[size - i], polynomial[i] = polynomial[i], polynomial[size - i]
    polynomial = NTT(polynomial, size, generator, modulus)
    for i in range(size):
        polynomial[i] = (modular_inverse(size, modulus) * polynomial[i]) % modulus
    return polynomial

def find_galois_field(k):
    '''
    we want to find a suitable field such that generator^(2^(k-1)) = -1 mod modulus
    and N = 2^(ak) + 1. This ensures that all polynomials are subject to constraint
    (size | modulus - 1) within the galois field.
    '''
    a = 1
    while 1:
        modulus = (a << k) + 1 #equivalent to 2^(ak) + 1
        for generator in range(2, a + 1):
            if modular_power(generator, 1 << (k - 1), modulus) == modulus - 1: # -1 mod modulus = modulus - 1
                return modulus, generator
        a += 1

def convolve(seq1, seq2):
    n = len(seq1)
    k = len(bin(n)) - 3 #-3 because python's shitty bin() function adds overhead
    modulus, generator = find_galois_field(k)
    NTT(seq1, len(seq1), generator, modulus)
    NTT(seq2, len(seq2), generator, modulus)
    convolved = [seq1[i] * seq2[i] for i in range(len(seq1))]
    return INTT(convolved, len(convolved), generator, modulus)

def multiply_coefs(x, y):    
        n = 1 << (len(bin(max(len(x),len(y))-1))-1)
        x = x + [0] * (n - len(x))
        y = y + [0] * (n - len(y))
        z = convolve(x, y)
        carry = 0
        non_zero = 0
        for i in range(len(z)):
            carry += z[i]
            z[i] = carry % 2
            if z[i] != 0:
                non_zero = i
            carry = carry / 2
        return z[:non_zero+1]
    
def multiply_NTT(num1, num2):
    num1Array = [int(digit) for digit in bin(num1)[:1:-1]]
    num2Array = [int(digit) for digit in bin(num2)[:1:-1]]
    answerArray = multiply_coefs(num1Array, num2Array)
    ans = 0
    for bit in reversed(answerArray):
        ans = (ans << 1) | int(bit)
    return ans

t = time.time()
print(multiply_NTT(523049394854, 2349394856594540))
print(f'{time.time() - t}s')