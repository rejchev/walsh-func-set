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
    W_API int32_t __stdcall pal(uint32_t n, double_t x);

// Walsh-Walsh numeration (sorted )
    W_API int32_t __stdcall wal(uint32_t n, double_t x);

// Walsh-Hadamard numeration ()
    W_API int32_t __stdcall had(uint32_t n, double_t x);

// Walsh multiplication (Walsh-Walsh)
    W_API int32_t __stdcall wal_multiply(uint32_t k, uint32_t m, double_t x);

// Normal binary number code to gray code conversation
    W_API uint32_t __stdcall binaryToGrayCode(uint32_t n);

// Gray code to normal binary number code conversation
    W_API uint32_t __stdcall grayCodeToBinary(uint32_t n);

// Gray code to Hadamard
    W_API uint32_t __stdcall grayCodeToHadamard(uint32_t n);

// Hadamard to Gray code
    W_API uint32_t __stdcall hadamardToGrayCode(uint32_t n);

// Binary reverse
    W_API uint32_t __stdcall bitReverse(uint32_t n);
}

#endif //WALSH_SYSTEM_W32_WALSHF32_H
