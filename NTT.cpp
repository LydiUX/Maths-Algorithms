//number theoretic transform
//doesn't work for multiplication larger than 2^16? idk why
#include <iostream>
#include <cmath>
#include <cstdint>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <bitset>
#include <ctime>

#pragma gcc optimise("Ofast")

using namespace std;

int64_t modularPower(int64_t a, int64_t b, int64_t modulus){
    if (a == 0){
        return 0;
    }
    int64_t result = 1;
    a %= modulus;
    while (b > 0){
        if ((b & 1) == 1){
            result *= a % modulus;
        }
        b >>= 1; //equivalent to b //= 2
        a *= a % modulus;
    }
    return result;
}

int64_t extendedGCD(int64_t a, int64_t b, int64_t* x, int64_t* y){
    if (a == 0){
        *x = 0;
        *y = 1;
        return b;
    }
    int64_t x1;
    int64_t y1;
    int64_t gcd = extendedGCD(b % a, a, &x1, &y1);
    *x = y1 - (b / a) * x1;
    *y = x1;
    return gcd;
}

int64_t modularInverse(int64_t a, int64_t modulus){
    int64_t x;
    int64_t y;
    int64_t gcd = extendedGCD(a, modulus, &x, &y);
    if (gcd != 1){
        throw invalid_argument("modular inverse doesn't exist");
    }
    return (x % modulus + modulus) % modulus; //need to add modulus to handle negative numbers
}

int64_t binary(int64_t a){
    int64_t result = 0;
    int64_t counter = 0;
    while (a != 0){
        int64_t remainder = a & 1;
        int64_t x = pow(10, counter);
        result += remainder * x;
        a >>= 1;
        counter++;
    }
    return result;
}

int64_t binaryLength(int64_t a){
    return int64_t(log10(a) + 1);
}

vector<int64_t> padVector(const vector<int64_t>& vec, int64_t targetSize){ 
    vector<int64_t> paddedVec = vec; //pad vectors with zeros to prepare for convolution (order 2^k)
    int64_t paddingSize = targetSize - vec.size();
    paddedVec.insert(paddedVec.end(), paddingSize, 0);
    return paddedVec;
}

vector<long double> convertInt64LongDouble(const vector<int64_t>& input){
    vector<long double> output;
    output.reserve(input.size());
    for (const auto& element : input){
        output.push_back(static_cast<long double>(element));
    }
    return output;
}

vector<int64_t> binaryAsVector(int64_t num){
    bitset<64> binary(num);
    vector<int64_t> digits;
    for (int64_t i = 63; i >= 0; i--){
        digits.push_back(binary[i]);
    }
    return digits;
}

int NTT(vector<int64_t>& polynomial, int64_t size, int64_t generator, int64_t modulus){
    /*
    size refers to the size of the polyonmial. The size of the polynomial is a power of 2; i.e. 2^k. Constraint: (size | modulus - 1).
    The maximum degree of the polynomial is n-1. 
    The generator is the primitive root of unity under the galois field F_modulus.
    & is needed in vector<int64_t>& as passing by reference is more efficient.
    */
    if (size == 1){
        return 1; //the function should return the original polynomail
    }
    vector<int64_t> polynomialEven; //divide and conquer
    vector<int64_t> polynomialOdd;
    for (int64_t i = 0; i < polynomial.size(); i += 2){
        polynomialEven.push_back(polynomial[i]);
    }
    for (int64_t i = 1; i < polynomial.size(); i += 2){
        polynomialOdd.push_back(polynomial[i]);
    }
    int64_t eval_point = modularPower(generator, 2, modulus);
    NTT(polynomialEven, size / 2, eval_point, modulus);
    NTT(polynomialOdd, size / 2, eval_point, modulus);
    for (int64_t i = 0; i < size / 2; i++){
        polynomial[i] = (int64_t)(polynomialEven[i] + pow(generator, i) * polynomialOdd[i]) % modulus;
        polynomial[i + size / 2] = (int64_t)(polynomialEven[i] + pow(generator, i + size / 2) * polynomialOdd[i]) % modulus;
    }
    return 0;
}

int INTT(vector<int64_t>& polynomial, int64_t size, int64_t generator, int64_t modulus){
    /*
    it's possible to reuse the NTT algorithm to compute the INTT. To find the coefficient form again,
    you need the inverse generator under the galois field F_modulus. The extended GCD algorithm is chosen
    to compute the inverse.
    */
    if (size == 1){
        return 1;
    }
    vector<int64_t> tempArray = polynomial;
    for (int64_t i = 1; i < (size + 1) / 2; i++){
        polynomial[i] = polynomial[size - i];
        polynomial[size - i] = tempArray[i];
    }
    NTT(polynomial, size, generator, modulus);
    for (int64_t i = 0; i < size; i++){
        polynomial[i] = (int64_t)((modularInverse(size, modulus) * polynomial[i]) % modulus);
    }
    return 0;
}

vector<int64_t> findGaloisField(int64_t k){
    /*we want to find a suitable field such that generator^(2^(k-1)) = -1 mod modulus
    and modulus = 2^(ak) + 1. This ensures that all polynomials are subject to constraint
    (size | modulus - 1) within the galois field.*/
    int64_t a = 1;
    while (1){
        int64_t modulus = (a << k) + 1;
        for (int64_t generator = 2; generator <= a; generator++){
            if (modularPower(generator, 1 << (k - 1), modulus) == modulus - 1){
                vector<int64_t> field = {modulus, generator};
                return field;
            }
        }
        a++;  
    }
}

vector<int64_t> convolve(vector<int64_t> seq1, vector<int64_t> seq2){
    int64_t k = binaryLength(binary(seq1.size())) - 1;
    vector<int64_t> field = findGaloisField(k);
    vector<int64_t> convolved(seq1.size()); // Resizing to the appropriate size
    int64_t modulus = field[0];
    int64_t generator = field[1];
    NTT(seq1, seq1.size(), generator, modulus);
    NTT(seq2, seq2.size(), generator, modulus);
    for (int64_t i = 0; i < seq1.size(); i++){
        convolved[i] = seq1[i] * seq2[i]; //via the convolution theorem
    }
    INTT(convolved, convolved.size(), generator, modulus);
    return convolved;
}

vector<long double> multiplyCoefs(vector<int64_t> x, vector<int64_t> y){
    int64_t n = 1 << (binaryLength(binary(max(x.size(), y.size()) - 1)) + 1);
    x = padVector(x, n);
    y = padVector(y, n);
    vector<int64_t> temp = convolve(x, y);
    vector<long double> z = convertInt64LongDouble(temp);
    long double carry = 0;
    int64_t nonZero = 0;
    for (int64_t i = 0; i < z.size(); i++){
        carry += z[i];
        z[i] = fmod(carry, 2);
        if (z[i] != 0){
            nonZero = i;
        }
        carry /= 2;
    }
    return vector<long double>(z.begin(), z.begin() + nonZero + 1); 
}

int64_t multiply_NTT(int64_t num1, int64_t num2){
    vector<int64_t> num1Array = binaryAsVector(num1);
    vector<int64_t> num2Array = binaryAsVector(num2);
    //reverse integers to prepare for NTT and remove trailing zeroes from vectors
    reverse(num1Array.begin(), num1Array.end());
    reverse(num2Array.begin(), num2Array.end());
    auto lastNonZero = find_if(num1Array.rbegin(), num1Array.rend(), [](int64_t digit) {
        return digit != 0;
    });
    num1Array.erase(lastNonZero.base(), num1Array.end());
    auto lastNonZero2 = find_if(num2Array.rbegin(), num2Array.rend(), [](int64_t digit) {
        return digit != 0;
    });
    num2Array.erase(lastNonZero2.base(), num2Array.end());
    vector<long double> answer = multiplyCoefs(num1Array, num2Array);
    int64_t result = 0;
    for (auto i = answer.rbegin(); i != answer.rend(); i++){
        int64_t bit = *i;
        result = (result << 1) | (int64_t)bit;
    }
    return result;
}

int main(){
    clock_t t;
    t = clock();
    printf("%lld\n", multiply_NTT(256, 256));
    t = clock() - t;
    printf("Time taken: %f seconds \n", ((double)t)/CLOCKS_PER_SEC);

    t = clock();
    printf("%d\n", 256 * 256);
    t = clock() - t;
    printf("Time taken: %f seconds \n", ((double)t)/CLOCKS_PER_SEC);
    /*
    vector<int64_t> polynomial = {1,4,4,3};
    printf("%lld\n", modularPower(4, 5, 9));
    printf("%lld\n", modularInverse(2, 5));
    NTT(polynomial, 4, 2, 5);
    for (int i = 0; i < polynomial.size(); i++){
        printf("%d: %lld\n", i + 1, polynomial[i]);
    }
    INTT(polynomial, 4, 2, 5);
    for (int i = 0; i < polynomial.size(); i++){
        printf("%d: %lld\n", i + 1, polynomial[i]);
    }
    vector<int64_t> galoisField = findGaloisField(4);
    for (int i = 0; i < galoisField.size(); i++){
        printf("%d: %lld\n", i + 1, galoisField[i]);
    }
    vector<int64_t> polynomial2 = {1,2,2,3};
    vector<int64_t> result;
    result = convolve(polynomial, polynomial2);
    for (int i = 0; i < result.size(); i++){
        printf("%d: %lld\n", i + 1, result[i]);
    }
    vector<long double> result2;
    result2 = multiplyCoefs(polynomial, polynomial2);
    for (int i = 0; i < result2.size(); i++){
        printf("%d: %lf\n", i + 1, result2[i]);
    }
    */
    return 0;
}