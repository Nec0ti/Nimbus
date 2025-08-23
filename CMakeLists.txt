cmake_minimum_required(VERSION 3.20)
project(NimbusEngine LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

# Fetch GLFW for windowing
FetchContent_Declare(
  glfw
  GIT_REPOSITORY https://github.com/glfw/glfw.git
  GIT_TAG        3.3.8
)
FetchContent_MakeAvailable(glfw)

# Fetch GLAD for OpenGL loader (fallback rendering)
FetchContent_Declare(
  glad
  GIT_REPOSITORY https://github.com/Dav1dde/glad.git
  GIT_TAG        v0.1.36
)
FetchContent_MakeAvailable(glad)

# Engine library
add_library(NimbusEngine STATIC)
file(GLOB_RECURSE ENGINE_SRC CONFIGURE_DEPENDS src/engine/*.cpp src/engine/*.h)
if(NOT ENGINE_SRC)
  # placeholder to avoid error when no sources exist yet
  set(ENGINE_SRC src/engine/placeholder.cpp)
endif()
add_library(NimbusEngine::Nimbus ALIAS NimbusEngine)

target_sources(NimbusEngine PRIVATE ${ENGINE_SRC})

target_include_directories(NimbusEngine PUBLIC src)

target_link_libraries(NimbusEngine PUBLIC glfw)

# Sandbox application
add_executable(Sandbox src/sandbox/main.cpp)

target_link_libraries(Sandbox PRIVATE NimbusEngine glad)

if (UNIX)
  target_link_libraries(Sandbox PRIVATE dl pthread)
endif()