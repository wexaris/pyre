#pragma once


//////////////////////// PLATFORM ////////////////////////

#ifdef _WIN32
    #ifdef _WIN64
        #define PYRE_PLATFORM_WINDOWS
    #else
        #error "x86 is not supported!"
    #endif
#elif defined(__APPLE__) || defined(__MACH__)
    #include <TargetConditionals.h>
    #if TARGET_IPHONE_SIMULATOR == 1
        #error "IOS simulator is not supported!"
    #elif TARGET_OS_IPHONE == 1
        #define PYRE_PLATFORM_IOS
        #error "IOS is not supported!"
    #elif TARGET_OS_MAC == 1
        #define PYRE_PLATFORM_MACOS
        #error "MacOS is not supported!"
    #else
        #error "Unknown platform!"
    #endif
#elif defined(__ANDROID__)
    #define PYRE_PLATFORM_ANDROID
    #error "Android is not supported!"
#elif defined(__linux__)
    #define PYRE_PLATFORM_LINUX
    #error "Linux is not supported!"
#else
   #error Unknown platform!
#endif


//////////////////////// BUILD TYPE ////////////////////////

#ifdef _DEBUG
    #define PYRE_DEBUG
#else
    #define PYRE_RELEASE
#endif

#ifdef PYRE_DEBUG
    #define PYRE_ENABLE_ASSERTS
    #define PYRE_ENABLE_PROFILE

    #if defined PYRE_PLATFORM_WINDOWS
        #define PYRE_DEBUGBREAK() __debugbreak()
    #elif defined PYRE_PLATFORM_LINUX
        #include <signal.h>
        #define PYRE_DEBUGBREAK() raise(SIGTRAP)
    #endif
#endif

#ifdef PYRE_ENABLE_ASSERTS
    #define PYRE_CORE_ASSERT(x, ...) { if (!(x)) { PYRE_CORE_ERROR("Assertion Failed: {}", __VA_ARGS__); PYRE_DEBUGBREAK(); } }
    #define PYRE_ASSERT(x, ...) { if (!(x)) { PYRE_ERROR("Assertion Failed: {}", __VA_ARGS__); PYRE_DEBUGBREAK(); } }
#else
    #define PYRE_CORE_ASSERT(x, ...)
    #define PYRE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)


//////////////////////// SETTINGS ////////////////////////

#define GLFW_INCLUDE_NONE // GLFW won't include its own OpenGL


//////////////////////// MEMORY ////////////////////////

#include <memory>

namespace Pyre {

    template<typename T>
    using Scope = std::unique_ptr<T>;

    template<typename T>
    using Ref = std::shared_ptr<T>;

    template<typename T, typename... Args>
    constexpr auto MakeScope(const Args&... args) {
        return std::make_unique<T>(args...);
    }

    template<typename T, typename... Args>
    constexpr auto MakeRef(const Args&... args) {
        return std::make_shared<T>(args...);
    }

}