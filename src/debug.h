#ifndef _CG_DEBUG_H
#define _CG_DEBUG_H

#ifdef DEBUG
    #define debugPrint(fmt, ...) printf(fmt, __VA_ARGS__)
#else
    #define debugPrint(fmt, ...)
#endif

#endif
