#ifndef WALSH_SYSTEM_W32_UTILS_H
#define WALSH_SYSTEM_W32_UTILS_H

#include <cstdint>

#include "../main.h"

W_API int32_t __stdcall bit_reverse(int32_t i, unsigned nbits);

W_API void __stdcall bit_print(int32_t i);

W_API int32_t __stdcall grayToBin(const int32_t&);
W_API int32_t __stdcall binToGray(const int32_t&);

#endif //WALSH_SYSTEM_W32_UTILS_H
