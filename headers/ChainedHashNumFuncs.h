
/* ChainedHashNumFuncs.h */

#ifndef _ChainedHashNumFuncs_h_
#define _ChainedHashNumFuncs_h_

    #include <stdlib.h>
    #include <stdbool.h>
    
    size_t rand_int(size_t min, size_t max);
    size_t next_prime(size_t number);
    size_t hash(size_t k, size_t a, size_t b, size_t p, size_t m);

#endif
