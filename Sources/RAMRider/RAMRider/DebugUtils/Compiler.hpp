#ifndef __PLATFORM_COMPILER_SPECIFIC_HPP__
#define __PLATFORM_COMPILER_SPECIFIC_HPP__

// Making platform (or compiler) specific stuff platform independent

#define MSVC        0x0A
#define GCC         0x0B
#define CLANG       0x0C
#define UNSUPPORTED 0x00

#if defined(_MSC_VER)
    #define COMPILER MSVC
#elif defined(__GNUC__)
    #ifndef __clang__ // fucking clang also defines __GNUC__
        #define COMPILER GCC
    #else
        #define COMPILER CLANG
    #endif
#else
    #define COMPILER UNSUPPORTED
#endif

#if (COMPILER == MSVC)
    #define COMPILER_DEBUG_BREAK() __debugbreak()
#elif (COMPILER == GCC)
    #define COMPILER_DEBUG_BREAK() __builtin_trap()
#elif (COMPILER == CLANG)
    #define COMPILER_DEBUG_BREAK() __builtin_debugtrap()
#else
    #define COMPILER_DEBUG_BREAK()
#endif

#endif