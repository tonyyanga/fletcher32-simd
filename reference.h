#include <stdint.h>
#include <stddef.h>

/* Reference implementation of Fletcher32, C code, not optimized
 * @param  data    pointer to input data, ideally aligned
 * @param  words   length of input data in terms of *uint16_t*
 * @param  a       sum counter 1 in fletcher algorithm, between 0 and 65535
 * @param  b       sum counter 2 in fletcher algorithm, between 0 and 65535
 */
uint32_t fletcher32_ref( uint16_t const *data, size_t words, uint32_t& a, uint32_t& b );

/* Naive C implementation for illustration
 * @param  data    pointer to input data, ideally aligned
 * @param  len   length of input data in terms of *uint16_t*
 * @param  a       sum counter 1 in fletcher algorithm, between 0 and 65535
 * @param  b       sum counter 2 in fletcher algorithm, between 0 and 65535
 */
uint32_t fletcher32_naive (uint16_t* data, size_t len, uint32_t& a, uint32_t& b);
