#include <stdio.h>
#include <stdint.h>
#include <time.h>

uint64_t modularInverse(uint64_t base, uint64_t modulus){ 
    uint64_t result = 1;
    uint64_t exponent = modulus - 2; //fermat's little theorem a^-1 = a^(p-2) mod p -> inverse = base^(modulus-2) mod modulus
    if (modulus == 1) {
        return 0;
    }
    for (uint64_t i = 0; i < exponent; i++){ //modular exponentiation for a^(p-2) mod p -> (a*b) mod p = (a mod p * b mod p) mod p
        result = (result * base) % modulus;
    }
    return result;
}

uint64_t factorialMod(uint64_t number, uint64_t modulus){
    uint64_t result = modulus - 1;
    if (number >= modulus){ //(number! mod modulus) = 0 where number >= modulus 
        return 0;
    }
    for (uint64_t i = number + 1; i < modulus; i++){ //Wilson's theorem (p-1)! = (p-1) mod p
        result = (modularInverse(i, modulus) * result) % modulus;
    }
    return result;
}

int main(){
    uint64_t number;
    uint64_t modulus;
    printf("Print the number (of which the factorial will be taken) and the modulus (must be prime) seperated by a space.\n");
    scanf("%llu %llu", &number, &modulus);
    clock_t t;
    t = clock();
    printf("%llu! mod %llu = %llu \n", number, modulus, factorialMod(number, modulus));
    t = clock() - t;
    printf("Time taken: %f seconds \n", ((double)t)/CLOCKS_PER_SEC);
    return 0;
}