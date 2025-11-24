// Separate Chaining Hash Table

#include<stdio.h>
#include<stdint.h>
#include<string.h>

// extern const uint64_t SCHT_FNV_OFFSET_BASIS_64;
// extern const uint64_t SCHT_FNV_PRIME;

#define SCHT_FNV_OFFSET_BASIS_64 14695981039346656037ULL
#define SCHT_FNV_PRIME64         1099511628211ULL



// hash function
uint64_t fnv_1a(const unsigned char *key);