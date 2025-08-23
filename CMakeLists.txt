cmake_minimum_required(VERSION 3.20)
project(NimbusEngine VERSION 1.0.0 LANGUAGES CXX C)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set build type
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

# Compiler-specific options
if(MSVC)
    add_compile_options(/W4 /WX)
    add_definitions(-D_CRT_SECURE_NO_WARNINGS)
    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
else()
    add_compile_options(-Wall -Wextra -Wpedantic -Werror)
endif()

# Platform detection
if(WIN32)
    set(NIMBUS_PLATFORM_WINDOWS TRUE)
    add_definitions(-DNIMBUS_PLATFORM_WINDOWS)
elseif(UNIX AND NOT APPLE)
    set(NIMBUS_PLATFORM_LINUX TRUE)
    add_definitions(-DNIMBUS_PLATFORM_LINUX)
endif()

# Build options
option(NIMBUS_BUILD_EDITOR "Build the Nimbus Editor" ON)
option(NIMBUS_BUILD_RUNTIME "Build the Nimbus Runtime" ON)
option(NIMBUS_BUILD_TESTS "Build unit tests" OFF)
option(NIMBUS_ENABLE_VULKAN "Enable Vulkan rendering backend" OFF)
option(NIMBUS_ENABLE_DIRECTX12 "Enable DirectX 12 rendering backend (Windows only)" OFF)

# Output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# Third-party dependencies
add_subdirectory(ThirdParty)

# Engine core
add_subdirectory(Engine)

# Editor application
if(NIMBUS_BUILD_EDITOR)
    add_subdirectory(Editor)
endif()

# Runtime library
if(NIMBUS_BUILD_RUNTIME)
    add_subdirectory(Runtime)
endif()

# Tests
if(NIMBUS_BUILD_TESTS)
    enable_testing()
    add_subdirectory(Tests)
endif()

# Install configuration
include(cmake/Install.cmake)

# Package configuration
include(cmake/Package.cmake)

# Print configuration summary
message(STATUS "Nimbus Engine Configuration:")
message(STATUS "  Build Type: ${CMAKE_BUILD_TYPE}")
message(STATUS "  Platform: ${CMAKE_SYSTEM_NAME}")
message(STATUS "  Compiler: ${CMAKE_CXX_COMPILER_ID}")
message(STATUS "  Build Editor: ${NIMBUS_BUILD_EDITOR}")
message(STATUS "  Build Runtime: ${NIMBUS_BUILD_RUNTIME}")
message(STATUS "  Enable Vulkan: ${NIMBUS_ENABLE_VULKAN}")
if(WIN32)
    message(STATUS "  Enable DirectX 12: ${NIMBUS_ENABLE_DIRECTX12}")
endif()