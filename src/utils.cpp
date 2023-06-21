#ifndef WALSH_EXPORTS
#define WALSH_EXPORTS 1
#endif

#include <iostream>
#include "utils.h"

W_API int32_t __stdcall bit_reverse(int32_t n, unsigned int nbits) {
    int32_t r = n;
    int32_t l, m;

    // Compute shift and bitmask
    l = (int32_t) (nbits - 1);
    m = (1 << nbits) - 1;

    // Permute
    while ( n >>= 1 )
    {
        r <<= 1;
        r |= n & 1;
        --l;
    }

    // Final shift and masking
    r <<= l;

    return r & m;
}

W_API void __stdcall bit_print(int32_t n) {

    static const unsigned b = sizeof(n);
    static char buf[b+1]; buf[b] = '\0';

    std::cout<< n;
    for (unsigned m = b; m; n >>= 1, --m)
        buf[m-1] = (n & 1) + '0';
    printf(" = %s\n",buf);
}

// https://en.wikipedia.org/wiki/Gray_code
W_API int32_t __stdcall grayToBin(const int32_t &n) {
    unsigned int buff = n;
    unsigned int bin;

    for (bin = 0; buff; buff >>= 1) {
        bin ^= n;
    }

    return bin;
}

// https://en.wikipedia.org/wiki/Gray_code
W_API int32_t __stdcall binToGray(const int32_t &n) {
    return n ^ ((n & 0xEEEEEEEE) >> 1);
}
