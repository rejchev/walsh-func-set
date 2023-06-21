#ifndef WALSH_SYSTEM_W32_MAIN_H
#define WALSH_SYSTEM_W32_MAIN_H

#ifdef WALSH_EXPORTS
#define W_API extern "C" __declspec(dllexport)
#else
#define W_API extern "C" __declspec(dllimport)
#endif

#endif //WALSH_SYSTEM_W32_MAIN_H
