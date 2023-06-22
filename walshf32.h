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

// Walsh-Hadamard numeration
//    W_API int32_t __stdcall had(uint32_t n, double_t x);

// Walsh multiplication
    W_API int32_t __stdcall wal_multiply(
            uint32_t k, uint32_t m, double_t x, int32_t (__stdcall *pWal)(uint32_t, double_t) = wal
    );

// Walsh sequence of n elems [must be free]
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

// Normal binary number code to gray code conversation
    W_API uint32_t __stdcall binaryToGrayCode(uint32_t n);

// Gray code to normal binary number code conversation
    W_API uint32_t __stdcall grayCodeToBinary(uint32_t n);

// Gray code to Hadamard
// 000 -> 000 | 0 -> 0
// 001 -> 100 | 1 -> 4
// 011 -> 110 | 3 -> 6
// 010 -> 010 | 2 -> 2
// 110 -> 011 | 6 -> 3
// 111 -> 111 | 7 -> 7
// 101 -> 101 | 5 -> 5
// 100 -> 001 | 4 -> 1
//    W_API uint32_t __stdcall grayCodeToHadamard(uint32_t n);

// Hadamard to Gray code
//    W_API uint32_t __stdcall hadamardToGrayCode(uint32_t n);

// Binary reverse
//    W_API uint32_t __stdcall bitReverse(uint32_t n);
}

#endif //WALSH_SYSTEM_W32_WALSHF32_H
