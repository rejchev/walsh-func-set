#ifndef WALSH_EXPORTS
#define WALSH_EXPORTS true
#endif

#include <cmath>

#include "walshf32.h"

W_API int32_t (__stdcall *RAD_DEFAULT_PTR) (int32_t, double) = radf::frad;

W_API int32_t __stdcall walshf::walp(uint32_t n, double x, int32_t (__stdcall *pRad)(int32_t, double)) {

    if(n == 0) return 1;

    int32_t i, k = 0, result = 1;

    while(n)
    {
        i = pRad(k, x);

        if(i && (n & 1) == 1)
            result *= i;

        k++; n >>= 1;
    }

    return result;
}

W_API int32_t __stdcall walshf::wal(uint32_t n, double x, int32_t (__stdcall *pRad)(int32_t, double)) {
    return walp(wal2pal(n), x, pRad);
}

W_API int32_t __stdcall walshf::walmul(
        uint32_t k,
        uint32_t m,
        double x,
        int32_t (__stdcall *pWal)(uint32_t, double, int32_t (__stdcall *)(int32_t, double)),
        int32_t (__stdcall *pRad)(int32_t, double)) {
    return pWal(k^m, x, pRad);
}

W_API int32_t * __stdcall walshf::walseq(
        uint32_t k,
        uint32_t n,
        double x,
        double dx,
        int32_t (__stdcall *pWal)(uint32_t, double, int32_t (__stdcall *)(int32_t, double)),
        int32_t (__stdcall *pRad)(int32_t, double)) {
    if(k >= n || pWal == nullptr) return nullptr;

    auto* seq = static_cast<int32_t *>(malloc(n * sizeof(int32_t)));

    for(uint32_t i = 0; i < n; i++) {
        *(seq + i) = pWal(k, x, pRad);

        x += dx;
    }

    return seq;
}

W_API uint32_t * __stdcall walshf::walbseq(
        uint32_t k,
        uint32_t n,
        double x,
        double dx,
        int32_t (__stdcall *pWal)(uint32_t, double, int32_t (__stdcall *)(int32_t, double)),
        int32_t (__stdcall *pRad)(int32_t, double)) {
    if(k >= n || pWal == nullptr) return nullptr;

    auto* seq = static_cast<uint32_t *>(malloc(n * sizeof(uint32_t)));

    for(uint32_t i = 0; i < n; i++)
    {
        *(seq + i) = wal2bin(pWal(k, x, pRad));

        x += dx;
    }

    return seq;
}

W_API int32_t* __stdcall walshf::walseq_log2(uint32_t k,
                                             uint32_t n,
                                             int32_t (__stdcall *pWal)(uint32_t, double, int32_t (__stdcall *)(int32_t, double)),
                                             int32_t (__stdcall *pRad)(int32_t, double)) {
    if(k >= n || pWal == nullptr) return nullptr;

    if((1 << static_cast<int32_t>(log2(n))) != n)
        return nullptr;

    const double dx = 1.0/n;

    return walseq(k, n, dx - 1.0/(2 * n), dx, pWal, pRad);
}

W_API uint32_t* __stdcall walshf::walbseq_log2(
        uint32_t k,
        uint32_t n,
        int32_t (__stdcall *pWal)(uint32_t, double, int32_t (__stdcall *)(int32_t, double)),
        int32_t (__stdcall *pRad)(int32_t, double)) {
    if(k >= n || pWal == nullptr) return nullptr;

    if((1 << static_cast<int32_t>(log2(n))) != n)
        return nullptr;

    const double dx = 1.0/n;

    return walbseq(k, n, dx - 1.0/(2 * n), dx, pWal, pRad);
}

W_API uint32_t __stdcall walshf::pal2wal(uint32_t n) {
    uint32_t bin;

    for (bin = 0; n; n >>= 1)
        bin ^= n;

    return bin;
}

W_API uint32_t __stdcall walshf::wal2pal(uint32_t n) {
    return n ^ (n >> 1);
}

W_API uint32_t __stdcall walshf::wal2bin(uint32_t value) {
    return value == -1 ? 1 : 0;
}

W_API int32_t __stdcall walshf::bin2wal(uint32_t value) {
    return value == 1 ? -1 : 1;
}