#include <cmath>

#include "radf.h"

namespace radf {

    int32_t rad(int32_t n, const double x)
    {
        if (n == -1)
            return 1;

        if( n < -1 )
            return 0;

        return (sin((2 << n) * M_PI * x) >= 0) ? 1 : -1;
    }

    int32_t frad(int32_t n, const double x) {

        if (n == -1)
            return 1;

        if(n < -1)
            return 0;

        // half-intervals count
        n = 2 << n;

        return ((((uint32_t) (x*n)) % 2) == 0) ? 1 : -1;
    }
}