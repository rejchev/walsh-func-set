#ifndef WALSH_SYSTEM_W32_WALSHF32_H
#define WALSH_SYSTEM_W32_WALSHF32_H

#ifdef WALSH_EXPORTS
    #define W_API extern "C" __declspec(dllexport)
#else
    #define W_API extern "C" __declspec(dllimport)
#endif

#include <radf.h>

namespace walshf {

    // Walsh–Paley numeration (known as Gray codes)
    W_API int32_t __stdcall walp(uint32_t n, double_t x);

    // Walsh-Walsh numeration (sorted )
    W_API int32_t __stdcall wal(uint32_t n, double_t x);

    // Walsh multiplication of k & m (func numbers)
    W_API int32_t __stdcall wal_multiply(
        uint32_t k,
        uint32_t m,
        double_t x,
        int32_t (__stdcall *pWal)(uint32_t, double_t) = wal);

    // Walsh sequence of n elems [must be freed]
    // @param k     number of function
    // @param n     elems count
    // @param x     x  (i0: wal(k, x); i1: wal(k, x + dx); ...)
    // @param dx    step x per iter
    // @param pWal  pointer to wal function [wal or walp]
    //
    // @return      nullptr on err/seq of n elems
    W_API int32_t* __stdcall wal_seq(
            uint32_t k,
            uint32_t n,
            double_t x,
            double_t dx,
            int32_t (__stdcall *pWal)(uint32_t, double_t) = wal);

    // Walsh sequence of n elems [must be freed]
    // @param k     number of function
    // @param n     elems count
    // @param x     x  (i0: wal(k, x); i1: wal(k, x + dx); ...)
    // @param dx    step x per iter
    // @param pWal  pointer to wal function [wal or walp]
    //
    // @return      nullptr on err/seq of n elems
    W_API uint32_t* __stdcall wal_binseq(
            uint32_t k,
            uint32_t n,
            double_t x,
            double_t dx,
            int32_t (__stdcall *pWal)(uint32_t, double_t) = wal);

    // Walsh sequence of n elems [must be freed]
    //
    //  x is calculating as x = (1/n - dx) with step: 1/n and dx: 1/(2n)
    //
    //  Example:
    //  1|--.--    --.--
    //   |------------------1--> x | '.' - (x - dx) = 1 or -1; step x: 1/n
    // -1|    __.__
    //
    // @param k     number of function
    // @param n     elems count = {n = 2^i, i in N0}
    // @param pWal  pointer to wal function [wal or walp]
    //
    // @return      nullptr on err/seq of n elems
    W_API int32_t* __stdcall wal_seq_log2(
            uint32_t k,
            uint32_t n,
            int32_t (__stdcall *pWal)(uint32_t, double_t) = wal);

    // Walsh binary sequence of n elems [must be freed]
    //
    //  x is calculating as x = (1/n - dx) with step: 1/n and dx: 1/(2n)
    //
    // @param k     number of function
    // @param n     elems count = {n = 2^i, i in N0}
    // @param pWal  pointer to wal function [wal or walp]
    //
    // @return      nullptr on err/seq of n elems
    W_API uint32_t* __stdcall wal_binseq_log2(
            uint32_t k,
            uint32_t n,
            int32_t (__stdcall *pWal)(uint32_t, double_t) = wal);

    // Normal binary number code to gray code conversation
    W_API uint32_t __stdcall bin2gray(uint32_t n);

    // Gray code to normal binary number code conversation
    W_API uint32_t __stdcall gray2bin(uint32_t n);

    // Walsh function result to bin conversion
    W_API uint32_t __stdcall wal2bin(uint32_t n);

    // Bin to normal walsh func result conversion
    W_API int32_t __stdcall bin2wal(uint32_t n);

}

#endif //WALSH_SYSTEM_W32_WALSHF32_H
