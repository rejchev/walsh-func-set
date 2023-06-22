#ifndef WALSH_EXPORTS
#define WALSH_EXPORTS true
#endif

#include "walshf32.h"

using namespace walshf;

W_API int32_t __stdcall walp(uint32_t n, double_t x) {

    if(n == 0) return 1;

    int32_t i, k = 0;
    double_t result = 1;

    while(n)
    {
        i = rademacher(k, x);

        if(i && (n & 1) == 1)
            result *= i;

        k++; n >>= 1;
    }

    return (int32_t)result;
}


W_API int32_t __stdcall wal(uint32_t n, double_t x) {
    return pal(binaryToGrayCode(n), x);
}

W_API int32_t __stdcall had(uint32_t n, double_t x) {
    return pal(hadamardToGrayCode(n), x);
}

W_API int32_t __stdcall wal_multiply(uint32_t k, uint32_t m, double_t x) {
    return wal(k^m, x);
}

W_API uint32_t __stdcall grayCodeToBinary(uint32_t n) {
    uint32_t bin;

    for (bin = 0; n; n >>= 1)
        bin ^= n;

    return bin;
}

W_API uint32_t __stdcall binaryToGrayCode(uint32_t n) {
    return n ^ ((n & 0xEEEEEEEE) >> 1);
}

// 100 -> 001, 110 -> 011, ...
W_API uint32_t __stdcall bitReverse(uint32_t n) {
    if(!n) return n;

    uint32_t output;
    for(output = 0; n; n >>= 1, output <<= 1)
        output |= (n & 1);

    return output;
}

// Gray -> Had
// 000 -> 000 | 0 -> 0
// 001 -> 100 | 1 -> 4
// 011 -> 110 | 3 -> 6
// 010 -> 010 | 2 -> 2
// 110 -> 011 | 6 -> 3
// 111 -> 111 | 7 -> 7
// 101 -> 101 | 5 -> 5
// 100 -> 001 | 4 -> 1
W_API uint32_t __stdcall grayCodeToHadamard(uint32_t n) {
    return bitReverse(n);
}

W_API uint32_t __stdcall hadamardToGrayCode(uint32_t n) {
    return bitReverse(n);
}


