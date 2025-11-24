// Separate Chaining Hash Table


#include "scht.h"

// extern const unsigned long SCHT_FNV_OFFSET_BASIS = 14695981039346656037;
// extern const unsigned long SCHT_FNV_PRIME = 1099511628211;

// extern const uint64_t SCHT_FNV_OFFSET_BASIS = 14695981039346656037;
// extern const uint64_t SCHT_FNV_PRIME = 1099511628211;
// extern const uint64_t SCHT_FNV_OFFSET_BASIS_64 = 14695981039346656037ULL;
// extern const uint64_t SCHT_FNV_PRIME = 1099511628211ULL;


uint64_t fnv_1a(const unsigned char *key) {
    uint64_t h = SCHT_FNV_OFFSET_BASIS_64;
    const unsigned char *b = key;

    // printf("\nUsing prime INSIDE = %llu\n", (unsigned long long)SCHT_FNV_PRIME64);


    while((*b) != '\0') {
        h = h ^ (*b);
        h = h * SCHT_FNV_PRIME64;
        b++;
    }
    return h;
    
    // for(int i = 0; i < strlen(key); i++) {
    //     h = h ^ key[i];
    //     h = h * SCHT_FNV_PRIME;
    // }
    // return h;
}
