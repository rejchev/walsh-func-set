#include "WalshSystem.h"

#include <radf.h>
#include <cmath>

namespace walsh {

    int32_t WalshSystem::wal(const int32_t &number, const double_t &x, int32_t (*func) (const int32_t&)) {
        if(number == 0)
            return 1;

        int32_t n = m_pConverter(number);

        if(func != nullptr)
            n = func(n);

        int32_t k = 0;
        double_t result = 1;

        while(n)
        {
            result *= pow(rademacher(k, x), (n & 1));

            k++;
            n >>= 1;
        }

        return (int32_t)round(result);
    }

    WalshSystem::WalshSystem() : m_pConverter(binToGray) {
    }

} // walsh