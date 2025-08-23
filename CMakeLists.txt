cmake_minimum_required(VERSION 3.20)
project(NimbusEngine VERSION 1.0.0 LANGUAGES CXX C)

# Set C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Build options
option(NIMBUS_BUILD_EDITOR "Build the editor GUI" ON)
option(NIMBUS_BUILD_TESTS "Build unit tests" OFF)
option(NIMBUS_BUILD_EXAMPLES "Build example projects" ON)
option(NIMBUS_VULKAN_ENABLED "Enable Vulkan rendering" ON)
option(NIMBUS_DIRECTX_ENABLED "Enable DirectX 12 (Windows only)" ON)
option(NIMBUS_OPENGL_ENABLED "Enable OpenGL rendering" ON)
option(NIMBUS_BUILD_SHARED "Build as shared library" OFF)

# Platform detection
if(WIN32)
    set(NIMBUS_PLATFORM_WINDOWS ON)
    set(NIMBUS_PLATFORM_NAME "Windows")
elseif(UNIX AND NOT APPLE)
    set(NIMBUS_PLATFORM_LINUX ON)
    set(NIMBUS_PLATFORM_NAME "Linux")
elseif(APPLE)
    set(NIMBUS_PLATFORM_MACOS ON)
    set(NIMBUS_PLATFORM_NAME "macOS")
endif()

# Compiler-specific settings
if(MSVC)
    add_compile_options(/W4 /utf-8)
    add_definitions(-D_CRT_SECURE_NO_WARNINGS)
else()
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# Find required packages
find_package(PkgConfig REQUIRED)

# Vulkan
if(NIMBUS_VULKAN_ENABLED)
    find_package(Vulkan REQUIRED)
    add_definitions(-DNIMBUS_VULKAN_ENABLED)
endif()

# OpenGL
if(NIMBUS_OPENGL_ENABLED)
    find_package(OpenGL REQUIRED)
    add_definitions(-DNIMBUS_OPENGL_ENABLED)
endif()

# DirectX (Windows only)
if(NIMBUS_PLATFORM_WINDOWS AND NIMBUS_DIRECTX_ENABLED)
    add_definitions(-DNIMBUS_DIRECTX_ENABLED)
endif()

# OpenAL
find_package(OpenAL REQUIRED)

# Bullet Physics
find_package(Bullet REQUIRED)

# GLFW for windowing
find_package(glfw3 REQUIRED)

# Dear ImGui
find_package(imgui REQUIRED)

# GLM for math
find_package(glm REQUIRED)

# STB for image loading
include(FetchContent)
FetchContent_Declare(
    stb
    GIT_REPOSITORY https://github.com/nothings/stb.git
    GIT_TAG master
)
FetchContent_MakeAvailable(stb)

# Include directories
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

# Source files
file(GLOB_RECURSE NIMBUS_CORE_SOURCES 
    "src/core/*.cpp"
    "src/core/*.c"
)

file(GLOB_RECURSE NIMBUS_RENDERING_SOURCES 
    "src/rendering/*.cpp"
    "src/rendering/*.c"
)

file(GLOB_RECURSE NIMBUS_PHYSICS_SOURCES 
    "src/physics/*.cpp"
    "src/physics/*.c"
)

file(GLOB_RECURSE NIMBUS_AUDIO_SOURCES 
    "src/audio/*.cpp"
    "src/audio/*.c"
)

file(GLOB_RECURSE NIMBUS_GUI_SOURCES 
    "src/gui/*.cpp"
    "src/gui/*.c"
)

file(GLOB_RECURSE NIMBUS_PLATFORM_SOURCES 
    "src/platform/*.cpp"
    "src/platform/*.c"
)

# Create Nimbus Engine library
if(NIMBUS_BUILD_SHARED)
    add_library(NimbusEngine SHARED
        ${NIMBUS_CORE_SOURCES}
        ${NIMBUS_RENDERING_SOURCES}
        ${NIMBUS_PHYSICS_SOURCES}
        ${NIMBUS_AUDIO_SOURCES}
        ${NIMBUS_GUI_SOURCES}
        ${NIMBUS_PLATFORM_SOURCES}
    )
else()
    add_library(NimbusEngine STATIC
        ${NIMBUS_CORE_SOURCES}
        ${NIMBUS_RENDERING_SOURCES}
        ${NIMBUS_PHYSICS_SOURCES}
        ${NIMBUS_AUDIO_SOURCES}
        ${NIMBUS_GUI_SOURCES}
        ${NIMBUS_PLATFORM_SOURCES}
    )
endif()

# Set library properties
set_target_properties(NimbusEngine PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION ${PROJECT_VERSION_MAJOR}
    PUBLIC_HEADER "${CMAKE_CURRENT_SOURCE_DIR}/include/nimbus/*.h"
)

# Link libraries
target_link_libraries(NimbusEngine
    OpenGL::GL
    glfw
    imgui::imgui
    glm::glm
    Bullet::BulletDynamics
    Bullet::BulletCollision
    Bullet::LinearMath
    OpenAL::AL
)

if(NIMBUS_VULKAN_ENABLED)
    target_link_libraries(NimbusEngine Vulkan::Vulkan)
endif()

# Platform-specific libraries
if(NIMBUS_PLATFORM_WINDOWS)
    target_link_libraries(NimbusEngine
        d3d12
        dxgi
        d3dcompiler
        xinput
    )
elseif(NIMBUS_PLATFORM_LINUX)
    target_link_libraries(NimbusEngine
        X11
        Xrandr
        Xinerama
        Xcursor
        Xi
    )
endif()

# Create Nimbus Editor executable
if(NIMBUS_BUILD_EDITOR)
    add_executable(NimbusEditor
        examples/editor/main.cpp
        examples/editor/EditorApplication.cpp
    )
    
    target_link_libraries(NimbusEditor NimbusEngine)
    
    # Set executable properties
    set_target_properties(NimbusEditor PROPERTIES
        OUTPUT_NAME "NimbusEngine"
        WIN32_EXECUTABLE ON
    )
endif()

# Create example projects
if(NIMBUS_BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()

# Create tests
if(NIMBUS_BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()

# Installation
install(TARGETS NimbusEngine
    EXPORT NimbusEngineTargets
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    RUNTIME DESTINATION bin
    PUBLIC_HEADER DESTINATION include/nimbus
)

install(DIRECTORY include/nimbus/
    DESTINATION include/nimbus
    FILES_MATCHING PATTERN "*.h"
)

if(NIMBUS_BUILD_EDITOR)
    install(TARGETS NimbusEditor
        RUNTIME DESTINATION bin
    )
endif()

# Export targets
install(EXPORT NimbusEngineTargets
    FILE NimbusEngineTargets.cmake
    NAMESPACE NimbusEngine::
    DESTINATION lib/cmake/NimbusEngine
)

# Create package configuration
include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    NimbusEngineConfigVersion.cmake
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY AnyNewerVersion
)

configure_package_config_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/cmake/NimbusEngineConfig.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/NimbusEngineConfig.cmake
    INSTALL_DESTINATION lib/cmake/NimbusEngine
)

install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/NimbusEngineConfig.cmake
    ${CMAKE_CURRENT_BINARY_DIR}/NimbusEngineConfigVersion.cmake
    DESTINATION lib/cmake/NimbusEngine
)

# Package generation
if(NIMBUS_PLATFORM_WINDOWS)
    set(CPACK_GENERATOR "NSIS")
    set(CPACK_PACKAGE_NAME "NimbusEngine")
    set(CPACK_PACKAGE_VERSION ${PROJECT_VERSION})
    set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Advanced 3D Game Engine")
    set(CPACK_PACKAGE_VENDOR "Nimbus Engine Team")
    set(CPACK_PACKAGE_INSTALL_DIRECTORY "NimbusEngine")
    set(CPACK_NSIS_ENABLE_ICON "${CMAKE_CURRENT_SOURCE_DIR}/assets/icon.ico")
    set(CPACK_NSIS_DISPLAY_NAME "Nimbus Engine")
    set(CPACK_NSIS_PACKAGE_NAME "Nimbus Engine")
    set(CPACK_NSIS_HELP_LINK "https://nimbus-engine.com")
    set(CPACK_NSIS_URL_INFO_ABOUT "https://nimbus-engine.com")
    set(CPACK_NSIS_CONTACT "support@nimbus-engine.com")
    set(CPACK_NSIS_MODIFY_PATH ON)
elseif(NIMBUS_PLATFORM_LINUX)
    set(CPACK_GENERATOR "TGZ")
    set(CPACK_PACKAGE_NAME "nimbus-engine")
    set(CPACK_PACKAGE_VERSION ${PROJECT_VERSION})
    set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Advanced 3D Game Engine")
    set(CPACK_PACKAGE_VENDOR "Nimbus Engine Team")
    set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE")
    set(CPACK_RESOURCE_FILE_README "${CMAKE_CURRENT_SOURCE_DIR}/README.md")
endif()

include(CPack)