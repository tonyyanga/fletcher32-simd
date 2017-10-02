#include <stdint.h>
#include <stddef.h>

/* Reference implementation of Fletcher32, C code, not optimized */
uint32_t fletcher32_ref( uint16_t const *data, size_t words, uint32_t& a, uint32_t& b );

/* Naive C implementation for illustration */
uint32_t fletcher32_naive (uint16_t* data, size_t len, uint32_t& a, uint32_t& b);
