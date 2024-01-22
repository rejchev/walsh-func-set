#ifndef TRAD_RADF_H
#define TRAD_RADF_H

#include <cstdint>

namespace radf {

    #define M_PI    3.14159265358979323846

    /**
     * @brief Rademacher functions set
     *
     *     based on http://mathscinet.ru/files/WalshFunctions.pdf
     *
     * @param n - function number (starting from -1 = [1, 1, 1, 1, 1])
     * @param x - value
     *
     * @return {1, -1} or 0 on n \< -1
     *
     **/
    int32_t rad(int32_t n, double x);

    /**
     * @brief Fast Rademacher functions set
     *
     *      based on half-intervals logic
     *
     * @param n - function number (starting from -1 = [1, 1, 1, 1, 1])
     * @param x - value
     *
     * @return  {1, -1} or 0 on n \< -1
     */
    int32_t frad(int32_t n, double x);
}


#endif //TRAD_RADF_H
