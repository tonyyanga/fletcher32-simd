#include <string.h>

#include "avx2.h"

typedef struct flecther_avx2 {
    uint32_t v[8] __attribute__((aligned(32)));
} fletcher_avx2;

/* AVX2 based implementation of Fletcher32 */
uint32_t fletcher32_avx2 (uint16_t* data, size_t len, uint32_t& a, uint32_t& b) {
    // Create ctx to store registers
    fletcher_avx2 ctx_a;
    fletcher_avx2 ctx_b;

    size_t tlen; // length to process in this batch

    uint64_t temp_b = b; // prevent overflow in b

    while (len >= 8) {
        tlen = (len >= 359) ? 359 : len;
        tlen = tlen - tlen % 8;
        len -= tlen;

        // Register usage:
        // YMM0 => ctx_a (sum1, a)
        // YMM1 => ctx_b (sum2, b)
        // YMM2 => input

        // Load context before start
        memset(&ctx_a, 0, sizeof(fletcher_avx2));
        memset(&ctx_b, 0, sizeof(fletcher_avx2));
        asm volatile("vmovdqu %0, %%ymm0" :: "m" (ctx_a));
        asm volatile("vmovdqu %0, %%ymm1" :: "m" (ctx_b));

        for (int i = 0; i < tlen; i += 8) {
            // Load data
            asm volatile("vpmovzxwd %0, %%ymm2"::"m" (*data));

            // Addition
            asm volatile("vpaddq %ymm0, %ymm2, %ymm0");
            asm volatile("vpaddq %ymm0, %ymm1, %ymm1");

            data += 8;
        }

        // Save context after loop
        asm volatile("vmovdqu %%ymm0, %0" : "=m" (ctx_a));
        asm volatile("vmovdqu %%ymm1, %0" : "=m" (ctx_b));

        asm volatile("vzeroupper");

        // Add ctx_a, ctx_b to a and b
        temp_b += tlen * a;

        for (int i = 0; i < 8; i++) {
            a += ctx_a.v[i];
            temp_b += 8 * ctx_b.v[i];
            temp_b -= i * ctx_a.v[i];
        }

        // Equivalent to a = a % 65535; b = b % 65535
        a = (a & 0xffff) + (a >> 16);
        temp_b = temp_b % 65535;
    }

    // update provided counter b
    b = temp_b;

    if (__builtin_expect((len > 0), 0)) {
        for (; len > 0; len--) {
            a += *data;
            b += a;

            data++;
        }
        a = (a & 0xffff) + (a >> 16);
        b = (b & 0xffff) + (b >> 16);
    }

    a = (a & 0xffff) + (a >> 16);
    b = (b & 0xffff) + (b >> 16);

    return (b << 16) | a;
}
