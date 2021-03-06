#include "reference.h"

/* Reference implementation of Fletcher32, C code, not optimized */
/* Source: https://en.wikipedia.org/wiki/Fletcher%27s_checksum#Fletcher-32 */
uint32_t fletcher32_ref( uint16_t const *data, size_t words, uint32_t& sum1, uint32_t& sum2 )
{
    size_t tlen;

    while (words) {
        tlen = ((words >= 359) ? 359 : words);
        words -= tlen;
        do {
            sum2 += sum1 += *data++;
            tlen--;
        } while (tlen);
        sum1 = (sum1 & 0xffff) + (sum1 >> 16);
        sum2 = (sum2 & 0xffff) + (sum2 >> 16);
    }
    /* Second reduction step to reduce sums to 16 bits */
    sum1 = (sum1 & 0xffff) + (sum1 >> 16);
    sum2 = (sum2 & 0xffff) + (sum2 >> 16);
    return (sum2 << 16) | sum1;
}

/* Naive C implementation for illustration */
uint32_t fletcher32_naive (uint16_t* data, size_t len, uint32_t& a, uint32_t& b) {
    while (len > 0) {
        a = (a + *data);
        b = (b + a);

        a = (a & 0xffff) + (a >> 16);
        b = (b & 0xffff) + (b >> 16);

        data++;
        len--;
    }

    // Require additional mod to ensure it is 0~65535
    a = (a & 0xffff) + (a >> 16);
    b = (b & 0xffff) + (b >> 16);

    return (b << 16) | a;
}
