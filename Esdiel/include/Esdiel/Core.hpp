#pragma once

// Compiler detection
#if defined(__clang__)
    #define ESDIEL_CXX_CLANG
    #define ESDIEL_CXX_NAME "LLVM/Clang " __VERSION__
#elif defined(__GNUG__)
    #define ESDIEL_CXX_GCC
    #define ESDIEL_CXX_NAME "GNU Compiler Collection " __VERSION__
#elif defined(_MSC_VER)
    #define ESDIEL_CXX_MSVC
    #define ESDIEL_CXX_NAME "Microsoft Visual C++ " _MSC_VER
#else
    #error "Unknown compiler"
#endif

// OS detection
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
    #define ESDIEL_OS_WINDOWS
#elif __linux__
    #define ESDIEL_OS_LINUX
#else
    #error "Unknown OS"
#endif

// Stringification
#define RV_STR(__name) #__name
#define RV_XSTR(__name) RV_STR(__name)

// Source file informations
#define ESDIEL_FILE __FILE__
#define ESDIEL_LINE __LINE__
#define ESDIEL_HERE ESDIEL_FILE ":" ESDIEL_XSTR(ESDIEL_LINE)

// Integer aliases
#include <cstdint>
