#pragma once

// Compiler detection
#if defined(__clang__)
    #define ESD_CXX_CLANG
    #define ESD_CXX_NAME "LLVM/Clang " __VERSION__
#elif defined(__GNUG__)
    #define ESD_CXX_GCC
    #define ESD_CXX_NAME "GNU Compiler Collection " __VERSION__
#elif defined(_MSC_VER)
    #define ESD_CXX_MSVC
    #define ESD_CXX_NAME "Microsoft Visual C++ " _MSC_VER
#else
    #error "Unknown compiler"
#endif

// OS detection
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
    #define ESD_OS_WINDOWS
#elif __linux__
    #define ESD_OS_LINUX
#else
    #error "Unknown OS"
#endif

// Stringification
#define ESD_STR(__name) #__name
#define ESD_XSTR(__name) ESD_STR(__name)

// Source file informations
#define ESD_FILE __FILE__
#define ESD_LINE __LINE__
#define ESD_HERE ESD_FILE ":" ESD_XSTR(ESD_LINE)

// Integer aliases
#include <cstdint>

// Asserting
#if defined(NDEBUG)
    #define ESD_ASSERT(__msg, __expr)
    #define ESD_JUST_ASSERT(__msg)
#else
    #include <cassert>
    #define ESD_ASSERT(__msg, __expr) assert((__msg) && (__expr))
    #define ESD_JUST_ASSERT(__msg) assert(!(__msg))
#endif
