#ifndef WALSH_SYSTEM_W32_IWALSHSYSTEM_H
#define WALSH_SYSTEM_W32_IWALSHSYSTEM_H

#include <cstdint>
#include <cmath>

class IWalshSystem
{
public:
    virtual int32_t wal(const int32_t&, const double_t&, int32_t (*numConverter) (const int32_t&)) =0;
};

#endif //WALSH_SYSTEM_W32_IWALSHSYSTEM_H
