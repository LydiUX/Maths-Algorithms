#number theoretic transform

def NTT(polynomial, size, generator, modulus): 
    '''
    Size refers to the size of the polyonmial. The size of the polynomial is a power of 2; i.e. 2^k. Constraint: (size | modulus - 1).
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

def INTT(polynomial, size, generator, modulus):
    if size == 1:
        return polynomial
    for i in range(1, (size + 1) // 2):
        polynomial[size - i], polynomial[i] = polynomial[i], polynomial[size - i]
    NTT(polynomial, size, generator, modulus)
    for i in range(size):
        polynomial[i] = (modular_inverse(size, modulus) * polynomial[i]) % modulus
    return polynomial

def modular_power(a, b, modulus):
    if a == 0:
        return 0 
    result = 1
    a %= modulus
    while b > 0:
        if b & 1 == 1:
            result *= a % modulus
        b >>= 1
        a *= a % modulus
    return result

def find_galois_field(k):
    '''
    we want to find a suitable field such that generator^(2^(k-1)) = -1 mod modulus
    and N = 2^(ak) + 1
    '''
    a = 1
    while 1:
        modulus = (a << k) + 1 #equivalent to 2^(ak) + 1
        for generator in range(2, a + 1):
            if modular_power(generator, 1 << (k - 1), modulus) == modulus - 1:
                return modulus, generator
        a += 1
    

assert(NTT([1,4,4,3], 4, 2, 5)) == [2,4,3,0]
assert(INTT([2,4,3,0], 4, 2, 5)) == [1,4,4,3]
assert(find_galois_field(4)) == (193, 3)
