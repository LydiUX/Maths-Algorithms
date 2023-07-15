#number theoretic transform

def NTT(polynomial, generator, ring):
    if len(polynomial) == 1: #number theoretic transform under galois field GF(ring)
        return polynomial #base case, can't NTT if polynomial has length 1
    polynomial_even = polynomial[::2] #divide and conquer!
    polynomial_odd = polynomial[1::2]
    eval_point = generator ** 2 % ring #evaluate each even/odd function at 2^(2k)
    NTT(polynomial_even, eval_point, ring)
    NTT(polynomial_odd, eval_point, ring)
    eval_point = 1
    for i in range(len(polynomial)):
        polynomial[i] = (polynomial_even[i % (len(polynomial) // 2)] + eval_point * polynomial_odd[i % (len(polynomial) // 2)]) % ring
        eval_point = (eval_point * generator) % ring
    return polynomial

def extended_gcd(a, b):
    if b == 0:
        return a, 1, 0
    else:
        gcd, x, y = extended_gcd(b, a % b)
        return gcd, y, x - (a // b) * y
    
def modular_inverse(a, m):
    gcd, x, _ = extended_gcd(a, m)
    if gcd != 1:
        raise ValueError
    else:
        return x % m

def INTT(polynomial, generator, ring):
    if len(polynomial) == 1:
        return polynomial
    for i in range(1, (len(polynomial) + 1) // 2):
        temp = polynomial[i]
        polynomial[i] = polynomial[len(polynomial) - i]
        polynomial[len(polynomial) - i] = temp
    NTT(polynomial, generator, ring)
    for i in range(len(polynomial)):
        polynomial[i] = (modular_inverse(len(polynomial), ring) * polynomial[i]) % ring
    return polynomial

print(NTT([1,4,4,3], 2, 5))
print(INTT([2,4,3,0], 2, 5))
