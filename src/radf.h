#ifndef TRAD_RADF_H
#define TRAD_RADF_H

#include <cmath>
#include <cstdint>

namespace radf {

    #define M_PI    3.14159265358979323846

    // radf(n,x) = sign(sin(2*pi*2^n*x)), x in [0, 1)
    // http://mathscinet.ru/files/WalshFunctions.pdf
    //
    // @return      1 or -1
    int32_t rad(int32_t n, double_t x);
}


#endif //TRAD_RADF_H
