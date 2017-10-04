#include <stdint.h>
#include <stddef.h>

/* AVX2 based implementation of Fletcher32 */
uint32_t fletcher32_avx2 (uint16_t* data, size_t len, uint32_t& a, uint32_t& b);
