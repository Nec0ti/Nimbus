# Third-party dependencies for Nimbus Engine

# GLFW - Window management
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory(glfw)

# GLM - Mathematics library
add_subdirectory(glm)

# Dear ImGui - Immediate mode GUI
set(IMGUI_SOURCES
    imgui/imgui.cpp
    imgui/imgui_demo.cpp
    imgui/imgui_draw.cpp
    imgui/imgui_tables.cpp
    imgui/imgui_widgets.cpp
    imgui/backends/imgui_impl_glfw.cpp
    imgui/backends/imgui_impl_opengl3.cpp
)

add_library(imgui STATIC ${IMGUI_SOURCES})
target_include_directories(imgui PUBLIC
    imgui
    imgui/backends
)
target_link_libraries(imgui PUBLIC glfw)

# GLAD - OpenGL loader
add_library(glad STATIC glad/src/glad.c)
target_include_directories(glad PUBLIC glad/include)

# stb - Image loading
add_library(stb_image INTERFACE)
target_include_directories(stb_image INTERFACE stb)

# Assimp - Asset loading
set(ASSIMP_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_ASSIMP_TOOLS OFF CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_SAMPLES OFF CACHE BOOL "" FORCE)
set(ASSIMP_INSTALL OFF CACHE BOOL "" FORCE)
add_subdirectory(assimp)

# FreeType - Font rendering
add_subdirectory(freetype)

# OpenAL Soft - Audio
if(NOT WIN32 OR NIMBUS_BUILD_OPENAL)
    set(ALSOFT_EXAMPLES OFF CACHE BOOL "" FORCE)
    set(ALSOFT_TESTS OFF CACHE BOOL "" FORCE)
    set(ALSOFT_UTILS OFF CACHE BOOL "" FORCE)
    add_subdirectory(openal-soft)
endif()

# Bullet Physics
set(BUILD_BULLET2_DEMOS OFF CACHE BOOL "" FORCE)
set(BUILD_BULLET3 OFF CACHE BOOL "" FORCE)
set(BUILD_CLSOCKET OFF CACHE BOOL "" FORCE)
set(BUILD_ENET OFF CACHE BOOL "" FORCE)
set(BUILD_EXTRAS OFF CACHE BOOL "" FORCE)
set(BUILD_OPENGL3_DEMOS OFF CACHE BOOL "" FORCE)
set(BUILD_UNIT_TESTS OFF CACHE BOOL "" FORCE)
add_subdirectory(bullet3)

# JSON - Configuration and serialization
add_library(nlohmann_json INTERFACE)
target_include_directories(nlohmann_json INTERFACE json/include)

# Platform-specific dependencies
if(NIMBUS_ENABLE_VULKAN)
    find_package(Vulkan REQUIRED)
endif()

if(WIN32 AND NIMBUS_ENABLE_DIRECTX12)
    # DirectX 12 is part of Windows SDK
    find_path(D3D12_INCLUDE_DIR d3d12.h HINTS ${DirectX_ROOT_DIR}/include)
    find_library(D3D12_LIBRARY d3d12 HINTS ${DirectX_ROOT_DIR}/lib)
endif()

# Create interface targets for easy linking
add_library(NimbusThirdParty INTERFACE)
target_link_libraries(NimbusThirdParty INTERFACE
    glfw
    glad
    imgui
    glm
    stb_image
    assimp
    freetype
    nlohmann_json
    BulletDynamics
    BulletCollision
    LinearMath
)

if(NOT WIN32 OR NIMBUS_BUILD_OPENAL)
    target_link_libraries(NimbusThirdParty INTERFACE OpenAL)
endif()

if(NIMBUS_ENABLE_VULKAN)
    target_link_libraries(NimbusThirdParty INTERFACE Vulkan::Vulkan)
endif()

if(WIN32 AND NIMBUS_ENABLE_DIRECTX12)
    target_link_libraries(NimbusThirdParty INTERFACE ${D3D12_LIBRARY})
    target_include_directories(NimbusThirdParty INTERFACE ${D3D12_INCLUDE_DIR})
endif()

# Platform-specific system libraries
if(WIN32)
    target_link_libraries(NimbusThirdParty INTERFACE
        opengl32
        gdi32
        winmm
        ole32
        oleaut32
        uuid
    )
elseif(UNIX AND NOT APPLE)
    target_link_libraries(NimbusThirdParty INTERFACE
        GL
        X11
        pthread
        dl
        m
    )
endif()