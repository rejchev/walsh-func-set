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
    return walp(binaryToGrayCode(n), x);
}

W_API int32_t __stdcall wal_multiply(
        uint32_t k,
        uint32_t m,
        double_t x,
        int32_t (__stdcall *pWal)(uint32_t, double_t)) {
    return pWal(k^m, x);
}

W_API int32_t * __stdcall wal_seq(
        uint32_t k,
        uint32_t n,
        double_t x,
        double_t dx,
        int32_t (__stdcall *pWal)(uint32_t, double_t)) {
    if(k >= n || pWal == nullptr) return nullptr;

    auto* seq = (int32_t*)malloc(n * sizeof(int32_t));

    for(uint32_t i = 0; i < n; i++) {
        *(seq + i) = pWal(k, x);

        x += dx;
    }

    return seq;
}

W_API int32_t * __stdcall wal_seq_log2(uint32_t k, uint32_t n, int32_t (__stdcall *pWal)(uint32_t, double_t)) {
    if(k >= n || pWal == nullptr) return nullptr;

    if((1 << (int32_t)log2(n)) != n)
        return nullptr;

    double_t dx = 1.0/n;
    double_t x = dx - 1.0/(2 * n);

    return wal_seq(k, n, x, dx, pWal);
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