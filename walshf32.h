#ifndef WALSH_SYSTEM_W32_WALSHF32_H
#define WALSH_SYSTEM_W32_WALSHF32_H

#ifdef WALSH_EXPORTS
    #define W_API extern "C" __declspec(dllexport)
#else
    #define W_API extern "C" __declspec(dllimport)
#endif

#include <radf.h>

namespace walshf {

    // default rad function implementation
    W_API int32_t (__stdcall *RAD_DEFAULT_PTR) (int32_t, double);

    /**
     * @brief Walsh functions
     *
     * @param n - function number (using Paley nums, starting from 0)
     * @param x - value
     *
     * @return {1, -1}
     *
     * */
    W_API int32_t __stdcall walp(uint32_t n, double x, int32_t (__stdcall *pRad)(int32_t, double) = RAD_DEFAULT_PTR);

    /**
     * @brief Walsh functions (sorted)
     *
     * @param n - function number (using Walsh nums, starting from 0)
     * @param x - value
     *
     * @return {1, -1}
     *
     * */
    W_API int32_t __stdcall wal(uint32_t n, double x, int32_t (__stdcall *pRad)(int32_t, double) = RAD_DEFAULT_PTR);

    /**
     * @brief Gets Walsh function result (using nums multiplication)
     *
     * @param k - function number (starting from 0)
     * @parma m - another function number (starting from 0)
     * @param x - value
     * @param pWal - pointer on Walsh functions set implementation (wal or walp)
     *
     * @return {1, -1} or 0 on n < 0
     *
     * */
    W_API int32_t __stdcall walmul(
        uint32_t k,
        uint32_t m,
        double x,
        int32_t (__stdcall *pWal)(uint32_t, double, int32_t (__stdcall *)(int32_t, double)) = wal,
        int32_t (__stdcall *pRad)(int32_t, double) = RAD_DEFAULT_PTR);

    /**
     * @brief Gets sequence of Walsh function results (must be freed via free)
     *
     * @param k - function number (starting from 0)
     * @param n - seq size
     * @param x - value
     * @param dx - value step
     * @param pWal - pointer on Walsh functions set implementation (wal or walp)
     *
     * @return  seq of {1, -1} vals on success,
     *          nullptr  on  k >= n or pWal = null
     *
     * */
    W_API int32_t* __stdcall walseq(
            uint32_t k,
            uint32_t n,
            double x,
            double dx,
            int32_t (__stdcall *pWal)(uint32_t, double, int32_t (__stdcall *)(int32_t, double)) = wal,
            int32_t (__stdcall *pRad)(int32_t, double) = RAD_DEFAULT_PTR);

    /**
     * @brief Gets binary sequence of Walsh function results (must be freed via free)
     *
     * @param k - function number (starting from 0)
     * @param n - seq size
     * @param x - value
     * @param dx - value step
     * @param pWal - pointer on Walsh functions set implementation (wal or walp)
     *
     * @return  seq of {1, -1} vals on success,
     *          nullptr  on  k >= n or pWal = null
     *
     * */
    W_API uint32_t* __stdcall walbseq(
            uint32_t k,
            uint32_t n,
            double x,
            double dx,
            int32_t (__stdcall *pWal)(uint32_t, double, int32_t (__stdcall *)(int32_t, double)) = wal,
            int32_t (__stdcall *pRad)(int32_t, double) = RAD_DEFAULT_PTR);

    /**
     * @brief Gets sequence of Walsh function results (must be freed via free)
     *
     * @param k - function number (starting from 0)
     * @param n - seq size (n = 2^m, m = 0,1,2,3 ....)
     * @param pWal - pointer on Walsh functions set implementation (wal or walp)
     *
     * @return  seq of {1, -1} vals on success,
     *          nullptr  on      k >= n
     *                       or  pWal = null
     *                       or  n is not pure log2 val
     *
     * */
    W_API int32_t* __stdcall walseq_log2(
            uint32_t k,
            uint32_t n,
            int32_t (__stdcall *pWal)(uint32_t, double, int32_t (__stdcall *)(int32_t, double)) = wal,
            int32_t (__stdcall *pRad)(int32_t, double) = RAD_DEFAULT_PTR);

    /**
     * @brief Gets binary sequence of Walsh function results (must be freed via free)
     *
     * @param k - function number (starting from 0)
     * @param n - seq size (n = 2^m, m = 0,1,2,3 ....)
     * @param pWal - pointer on Walsh functions set implementation (wal or walp)
     *
     * @return  seq of {1, -1} vals on success,
     *          nullptr  on      k >= n
     *                       or  pWal = null
     *                       or  n is not pure log2 val
     *
     * */
    W_API uint32_t* __stdcall walbseq_log2(
            uint32_t k,
            uint32_t n,
            int32_t (__stdcall *pWal)(uint32_t, double, int32_t (__stdcall *)(int32_t, double)) = wal,
            int32_t (__stdcall *pRad)(int32_t, double) = RAD_DEFAULT_PTR);

    /**
     * @brief Walsh to Paley nums conversation
     *
     *   (normal values to Gray codes conversion)
     *
     * @param n - source num
     *
     * @return Paley num
     *
     * */
    W_API uint32_t __stdcall wal2pal(uint32_t n);

    /**
     * @brief Paley to Walsh nums conversation
     *
     *   (Gray codes to normal values conversion)
     *
     * @param n - source num
     *
     * @return Walsh num
     *
     * */
    W_API uint32_t __stdcall pal2wal(uint32_t n);

    /**
     * @brief Walsh to binary conversion
     *
     *   (func results {1, -1} to binary {1, 0} conversion)
     *
     * @param n - value {1, -1}
     *
     * @return 1 on -1
     *         0 on 1
     *
     * */
    W_API uint32_t __stdcall wal2bin(uint32_t n);

    /**
     * @brief Binary to Walsh conversion
     *
     *   (binary {1, 0} to func results {1, -1} conversion)
     *
     * @param n - value {1, -1}
     *
     * @return 1 on -1
     *         0 on 1
     *
     * */
    W_API int32_t __stdcall bin2wal(uint32_t n);

}

#endif //WALSH_SYSTEM_W32_WALSHF32_H
