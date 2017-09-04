#include <stdio.h>
#include <string.h>
#include <tmmintrin.h>
#include <wmmintrin.h>

extern void aesenc (uint8_t *s, const uint8_t *rk);
extern void aesenclast (uint8_t *s, const uint8_t *rk);

int main () {
    uint8_t rk[16], s[16], s0[16];
    __m128i rk128, s128;

    for (int i = 0; i < 16; ++i) rk[i] = i;
    for (int i = 0; i < 16; ++i) s[i] = i;
    rk128 = _mm_load_si128 ((__m128i *)rk);
    s128 = _mm_load_si128 ((__m128i *)s);

    aesenc (s, rk);
    s128 = _mm_aesenc_si128 (s128, rk128);
    _mm_storeu_si128 ((__m128i *)s0, s128);

    if (!memcmp(s,s0,16)) printf("aesenc ok\n");
    else printf("aesenc fail\n");

    rk128 = _mm_load_si128 ((__m128i *)rk);
    s128 = _mm_load_si128 ((__m128i *)s);

    aesenclast (s, rk);
    s128 = _mm_aesenclast_si128 (s128, rk128);
    _mm_storeu_si128 ((__m128i *)s0, s128);

    if (!memcmp(s,s0,16)) printf("aesenclast ok\n");
    else printf("aesenclast fail\n");
}
