#include "radf.h"

namespace radf {

    int32_t rad(int32_t n, const double_t x)
    {
        if (n == -1)
            return 1;

        if( n < -1 )
            return 0;

        return (sin((2 << n) * M_PI * x) >= 0) ? 1 : -1;
    }
}
