def bn(num):
    binArray = []
    while not num < 1:
        binArray.append(num % 2)
        num = num // 2
    binArray.reverse()
    return sum(x * 10**i for i, x in enumerate(binArray[::-1]))

def dec(num):
    decArray = [int(i) for i in str(num)]
    return sum(x * 2**i for i, x in enumerate(decArray[::-1]))

def bitwiseShiftLeft(num, shiftIndex):
    shifted = [int(i) for i in str(num)]
    for _ in range(shiftIndex):
        shifted.append(0)
    return sum(x * 10**i for i, x in enumerate(shifted[::-1]))

def bitwiseShiftRight(num, shiftIndex):
    shifted = [int(i) for i in str(num)]
    if shiftIndex >= len(shifted):
        for _ in range(shiftIndex):
            shifted.pop()
        return sum(x * 10**i for i, x in enumerate(shifted[::-1]))

def bitwiseMultiply(a, b: int) -> int:
    if a == 0 or b == 0:
        return 0
    if b & 1 == 0:
        return bitwiseMultiply(a<<1, b>>1)
    else:
        return a + bitwiseMultiply(a<<1, (b-1)>>1)

assert bitwiseMultiply(2,4) == 8
