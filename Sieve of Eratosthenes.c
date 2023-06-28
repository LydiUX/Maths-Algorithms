#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

int* sieve(int n) {
    bool primeList[n + 1];
    for (int i = 0; i < n + 1; i++) {
        primeList[i] = true; // set all values within list to true, or a prime number
    }
    primeList[0] = true; // set 0 as not prime
    primeList[1] = true; // set 1 as not prime
    for (int i = 2; i * i <= n; i++) { // starting from 2
        if (primeList[i]) { // check if value within list is true
            for (int j = i * i; j <= n; j += i) { // if it is true, get rid of all its multiples
                primeList[j] = false; // set the multiples to false, not a prime number
            }
        }
    }
    int* primes = (int*)malloc((n + 1) * sizeof(int)); // dynamically allocated array because we don't know how long primes list is
    int counter = 0;
    for (int i = 0; i <= n; i++) {
        if (primeList[i]) {
            primes[counter] = i;
            counter++;
        }
    }
    primes[counter] = -1; //end of the primes list
    return primes; // left with all the primes below n
}

int main() {
    int n = 100;
    int* primes = sieve(n);
    for (int i = 0; primes[i] != -1; i++) {
        printf("%d: %d\n", i + 1, primes[i]);
    }
    free(primes); // deallocate the dynamically allocated array
    return 0;
}
