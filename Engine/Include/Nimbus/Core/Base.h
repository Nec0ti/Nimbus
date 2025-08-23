#pragma once

#include <memory>
#include <stdint.h>

// Platform detection
#ifdef _WIN32
    #ifdef _WIN64
        #define NIMBUS_PLATFORM_WINDOWS
    #else
        #error "x86 builds are not supported!"
    #endif
#elif defined(__linux__)
    #define NIMBUS_PLATFORM_LINUX
#else
    #error "Unknown platform!"
#endif

// API macros
#ifdef NIMBUS_PLATFORM_WINDOWS
    #ifdef NIMBUS_BUILD_DLL
        #define NIMBUS_API __declspec(dllexport)
    #else
        #define NIMBUS_API __declspec(dllimport)
    #endif
#else
    #define NIMBUS_API __attribute__((visibility("default")))
#endif

// Debug macros
#ifdef NIMBUS_DEBUG
    #define NIMBUS_ENABLE_ASSERTS
    #define NIMBUS_ENABLE_PROFILING
#endif

// Assertions
#ifdef NIMBUS_ENABLE_ASSERTS
    #define NIMBUS_ASSERT(x, ...) { if(!(x)) { NIMBUS_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
    #define NIMBUS_CORE_ASSERT(x, ...) { if(!(x)) { NIMBUS_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
    #define NIMBUS_ASSERT(x, ...)
    #define NIMBUS_CORE_ASSERT(x, ...)
#endif

// Bit manipulation
#define BIT(x) (1 << x)

// Bind event function
#define NIMBUS_BIND_EVENT_FN(fn) [this](auto&&... args) -> decltype(auto) { return this->fn(std::forward<decltype(args)>(args)...); }

// Memory management
namespace Nimbus {
    
    template<typename T>
    using Scope = std::unique_ptr<T>;
    template<typename T, typename ... Args>
    constexpr Scope<T> CreateScope(Args&& ... args)
    {
        return std::make_unique<T>(std::forward<Args>(args)...);
    }
    
    template<typename T>
    using Ref = std::shared_ptr<T>;
    template<typename T, typename ... Args>
    constexpr Ref<T> CreateRef(Args&& ... args)
    {
        return std::make_shared<T>(std::forward<Args>(args)...);
    }
    
    // Basic types
    using uint8 = uint8_t;
    using uint16 = uint16_t;
    using uint32 = uint32_t;
    using uint64 = uint64_t;
    
    using int8 = int8_t;
    using int16 = int16_t;
    using int32 = int32_t;
    using int64 = int64_t;
    
    using float32 = float;
    using float64 = double;
    
    // UUID type for asset management
    class UUID
    {
    public:
        UUID();
        UUID(uint64 uuid);
        UUID(const UUID&) = default;
        
        operator uint64() const { return m_UUID; }
        
    private:
        uint64 m_UUID;
    };
    
    // Non-copyable base class
    class NonCopyable
    {
    protected:
        NonCopyable() = default;
        ~NonCopyable() = default;
        
    private:
        NonCopyable(const NonCopyable&) = delete;
        NonCopyable& operator=(const NonCopyable&) = delete;
    };
}

// Hash specialization for UUID
namespace std {
    template<>
    struct hash<Nimbus::UUID>
    {
        std::size_t operator()(const Nimbus::UUID& uuid) const
        {
            return hash<uint64_t>()((uint64_t)uuid);
        }
    };
}