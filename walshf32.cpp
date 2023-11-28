#ifndef WALSH_EXPORTS
#define WALSH_EXPORTS true
#endif

#include "walshf32.h"

W_API int32_t __stdcall walshf::walp(uint32_t n, double_t x) {

    if(n == 0) return 1;

    int32_t i, k = 0, result = 1;

    while(n)
    {
        i = radf::rad(k, x);

        if(i && (n & 1) == 1)
            result *= i;

        k++; n >>= 1;
    }

    return result;
}

W_API int32_t __stdcall walshf::wal(uint32_t n, double_t x) {
    return walp(bin2gray(n), x);
}

W_API int32_t __stdcall walshf::wal_multiply(
        uint32_t k,
        uint32_t m,
        double_t x,
        int32_t (__stdcall *pWal)(uint32_t, double_t)) {
    return pWal(k^m, x);
}

W_API int32_t * __stdcall walshf::wal_seq(
        uint32_t k,
        uint32_t n,
        double_t x,
        double_t dx,
        int32_t (__stdcall *pWal)(uint32_t, double_t)) {
    if(k >= n || pWal == nullptr) return nullptr;

    auto* seq = static_cast<int32_t *>(malloc(n * sizeof(int32_t)));

    for(uint32_t i = 0; i < n; i++) {
        *(seq + i) = pWal(k, x);

        x += dx;
    }

    return seq;
}

W_API uint32_t * __stdcall walshf::wal_binseq(
        uint32_t k,
        uint32_t n,
        double_t x,
        double_t dx,
        int32_t (__stdcall *pWal)(uint32_t, double_t)) {
    if(k >= n || pWal == nullptr) return nullptr;

    auto* seq = static_cast<uint32_t *>(malloc(n * sizeof(uint32_t)));

    for(uint32_t i = 0; i < n; i++)
    {
        *(seq + i) = wal2bin(pWal(k, x));

        x += dx;
    }

    return seq;
}

W_API int32_t* __stdcall walshf::wal_seq_log2(uint32_t k, uint32_t n, int32_t (__stdcall *pWal)(uint32_t, double_t)) {
    if(k >= n || pWal == nullptr) return nullptr;

    if((1 << static_cast<int32_t>(log2(n))) != n)
        return nullptr;

    const double_t dx = 1.0/n;

    return wal_seq(k, n, dx - 1.0/(2 * n), dx, pWal);
}

W_API uint32_t* __stdcall walshf::wal_binseq_log2(uint32_t k, uint32_t n, int32_t (__stdcall *pWal)(uint32_t, double_t)) {
    if(k >= n || pWal == nullptr) return nullptr;

    if((1 << static_cast<int32_t>(log2(n))) != n)
        return nullptr;

    const double_t dx = 1.0/n;

    return wal_binseq(k, n, dx - 1.0/(2 * n), dx, pWal);
}

W_API uint32_t __stdcall walshf::gray2bin(uint32_t n) {
    uint32_t bin;

    for (bin = 0; n; n >>= 1)
        bin ^= n;

    return bin;
}

W_API uint32_t __stdcall walshf::bin2gray(uint32_t n) {
    return n ^ (n >> 1);
}

W_API uint32_t __stdcall walshf::wal2bin(uint32_t value) {
    return value == -1 ? 1 : 0;
}

W_API int32_t __stdcall walshf::bin2wal(uint32_t value) {
    return value == 1 ? -1 : 1;
}