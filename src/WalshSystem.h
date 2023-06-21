#ifndef WALSH_SYSTEM_W32_WALSHSYSTEM_H
#define WALSH_SYSTEM_W32_WALSHSYSTEM_H

#include <IWalshSystem.h>

#include "utils.h"

namespace walsh {

    class WalshSystem : public IWalshSystem {
    public:
        WalshSystem();

    public:
        int32_t wal(const int32_t&, const double_t&, int32_t (*numConverter) (const int32_t&) = nullptr) override;

    private:
        int32_t (__stdcall *m_pConverter)(const int32_t&);
    };

} // walsh

#endif //WALSH_SYSTEM_W32_WALSHSYSTEM_H
