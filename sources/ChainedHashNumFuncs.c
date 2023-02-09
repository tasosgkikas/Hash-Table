
#include "ChainedHashNumFuncs.h"

/* Returns a random integer in the given interval [min, max). */
size_t rand_int(size_t min, size_t max) {
    return min + ((double)rand()/(double)RAND_MAX)*(max - min);
}

/* Returns true if the given number is prime, else false. */
bool _is_prime(size_t number) {
    if (number <= 1) return false;
    for (size_t i = 2; i*i < number; i++)
        if (number % i == 0) return false;
    return true;
}

/* Returns the smallest prime that is larger than the given number. */
size_t next_prime(size_t number) {
    size_t p = number + 1;
    while (!_is_prime(p)) p++;
    return p;
}

/* Returns the hash value of the universal hash function with the given key k, table-size m and universal-hash-function-initializers a, b and p.  */
size_t hash(size_t k, size_t a, size_t b, size_t p, size_t m) {
    return ((a*k+b) % p) % m;
}
