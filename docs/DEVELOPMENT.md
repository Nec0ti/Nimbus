# Nimbus Engine Development Guide

This document provides comprehensive information for developers contributing to the Nimbus Engine project.

## Table of Contents

1. [Project Overview](#project-overview)
2. [Architecture](#architecture)
3. [Development Setup](#development-setup)
4. [Code Style](#code-style)
5. [Building](#building)
6. [Testing](#testing)
7. [Contributing](#contributing)
8. [Debugging](#debugging)
9. [Performance](#performance)
10. [Release Process](#release-process)

## Project Overview

The Nimbus Engine is a professional-grade 3D game engine designed to rival Unity in functionality and user experience. It features:

- **Multi-threaded Architecture**: Job system for rendering, physics, and game logic
- **Advanced Rendering**: Forward+ and Deferred pipelines with PBR materials
- **Unity-Style GUI**: Complete editor interface with dockable panels
- **Cross-Platform Support**: Windows, Linux, and macOS
- **Multiple Graphics APIs**: Vulkan, OpenGL, and DirectX 12
- **Physics Engine**: Bullet Physics integration
- **Audio System**: OpenAL-based 3D spatial audio
- **Scripting**: C# scripting API with hot reloading

## Architecture

### Core Systems

```
Nimbus Engine
├── Core Engine
│   ├── Engine (Main coordinator)
│   ├── Application (App-specific logic)
│   ├── Scene Management
│   ├── GameObject System
│   └── Component System
├── Rendering
│   ├── RenderAPI (Graphics API abstraction)
│   ├── RenderPipeline (Forward/Deferred)
│   ├── Material System
│   ├── Mesh System
│   ├── Shader System
│   └── Texture System
├── Physics
│   ├── PhysicsEngine (Bullet integration)
│   ├── Rigidbody
│   ├── Colliders
│   └── Constraints
├── Audio
│   ├── AudioEngine (OpenAL integration)
│   ├── AudioSource
│   └── AudioListener
├── GUI
│   ├── Editor (Main editor interface)
│   ├── Panels (Hierarchy, Inspector, etc.)
│   ├── MenuBar
│   ├── Toolbar
│   └── StatusBar
└── Platform
    ├── Window Management
    ├── Input System
    └── File System
```

### Component System

The engine uses a component-based architecture similar to Unity:

- **GameObject**: Container for components
- **Transform**: Position, rotation, scale (always present)
- **Component**: Base class for all components
- **Component Types**: Renderer, Camera, Light, Audio, Physics, Script

### Rendering Pipeline

1. **Forward+ Rendering**: Efficient for scenes with many lights
2. **Deferred Rendering**: Better for complex lighting scenarios
3. **Post-Processing**: Bloom, SSAO, SSR, TAA
4. **Global Illumination**: Light probes and reflection probes

## Development Setup

### Prerequisites

- **CMake** 3.20 or later
- **C++20** compatible compiler (GCC 10+, Clang 12+, MSVC 2019+)
- **Vulkan SDK** 1.3 or later
- **OpenGL** 4.6 or later
- **OpenAL** development libraries
- **Bullet Physics** 3.25 or later
- **GLFW** 3.3 or later
- **GLM** for mathematics
- **Dear ImGui** for GUI
- **spdlog** for logging

### Linux Setup (Ubuntu/Debian)

```bash
# Install dependencies
sudo apt update
sudo apt install build-essential cmake ninja-build
sudo apt install libgl1-mesa-dev libglfw3-dev libglm-dev
sudo apt install libbullet-dev libopenal-dev
sudo apt install vulkan-tools vulkan-validationlayers
sudo apt install libspdlog-dev

# Install ImGui (if not available in package manager)
git clone https://github.com/ocornut/imgui.git
cd imgui
mkdir build && cd build
cmake .. && make && sudo make install
```

### Linux Setup (Arch Linux)

```bash
# Install dependencies
sudo pacman -S base-devel cmake ninja
sudo pacman -S mesa glfw-x11 glm bullet openal
sudo pacman -S vulkan-tools vulkan-validation-layers
sudo pacman -S spdlog

# Install ImGui
sudo pacman -S imgui
```

### Windows Setup

1. **Install Visual Studio 2019/2022** with C++ development tools
2. **Install CMake** from https://cmake.org/
3. **Install Vulkan SDK** from https://vulkan.lunarg.com/
4. **Install vcpkg** for package management:
   ```cmd
   git clone https://github.com/Microsoft/vcpkg.git
   cd vcpkg
   .\bootstrap-vcpkg.bat
   .\vcpkg integrate install
   .\vcpkg install glfw3 glm bullet3 openal-soft spdlog imgui
   ```

### macOS Setup

```bash
# Install dependencies via Homebrew
brew install cmake ninja
brew install glfw glm bullet openal-soft
brew install vulkan-headers vulkan-tools
brew install spdlog imgui
```

## Code Style

### General Guidelines

- Use **C++20** features where appropriate
- Follow **RAII** principles
- Use **smart pointers** (std::unique_ptr, std::shared_ptr)
- Prefer **const correctness**
- Use **explicit** constructors for single-parameter constructors
- Use **override** keyword for virtual function overrides

### Naming Conventions

- **Classes**: PascalCase (e.g., `GameObject`, `Transform`)
- **Functions**: PascalCase (e.g., `Initialize()`, `Update()`)
- **Variables**: camelCase (e.g., `gameObject`, `transform`)
- **Constants**: UPPER_SNAKE_CASE (e.g., `MAX_GAME_OBJECTS`)
- **Namespaces**: PascalCase (e.g., `Nimbus`)
- **Files**: PascalCase (e.g., `GameObject.h`, `Transform.cpp`)

### File Organization

```
src/
├── core/
│   ├── Engine.cpp
│   ├── GameObject.cpp
│   ├── Component.cpp
│   └── Scene.cpp
├── rendering/
│   ├── Renderer.cpp
│   ├── Material.cpp
│   └── Mesh.cpp
└── gui/
    ├── Editor.cpp
    └── Panel.cpp
```

### Documentation

- Use **Doxygen** comments for all public APIs
- Include **@brief** descriptions for classes and functions
- Document **parameters** and **return values**
- Provide **usage examples** for complex APIs

Example:
```cpp
/**
 * @brief Represents a 3D transform with position, rotation, and scale
 * 
 * The Transform component is automatically added to every GameObject and
 * cannot be removed. It handles the position, rotation, and scale of
 * GameObjects in 3D space, including parent-child transformations.
 */
class Transform : public Component {
public:
    /**
     * @brief Get the world position
     * @return World position vector
     */
    glm::vec3 GetWorldPosition() const;
};
```

## Building

### Quick Build

```bash
# Linux/macOS
./scripts/build.sh

# Windows
scripts\build.bat
```

### Manual Build

```bash
# Create build directory
mkdir build && cd build

# Configure
cmake .. -DCMAKE_BUILD_TYPE=Release

# Build
make -j$(nproc)  # Linux/macOS
# or
cmake --build . --config Release --parallel  # Windows
```

### Build Options

- `-DNIMBUS_BUILD_EDITOR=ON/OFF`: Build the editor GUI
- `-DNIMBUS_BUILD_TESTS=ON/OFF`: Build unit tests
- `-DNIMBUS_BUILD_EXAMPLES=ON/OFF`: Build example projects
- `-DNIMBUS_VULKAN_ENABLED=ON/OFF`: Enable Vulkan rendering
- `-DNIMBUS_OPENGL_ENABLED=ON/OFF`: Enable OpenGL rendering
- `-DNIMBUS_DIRECTX_ENABLED=ON/OFF`: Enable DirectX 12 (Windows only)

## Testing

### Unit Tests

```bash
# Build with tests enabled
cmake .. -DNIMBUS_BUILD_TESTS=ON
make

# Run tests
ctest --output-on-failure
```

### Integration Tests

```bash
# Run integration tests
./tests/integration/run_tests.sh
```

### Performance Tests

```bash
# Run performance benchmarks
./tests/performance/run_benchmarks.sh
```

## Contributing

### Development Workflow

1. **Fork** the repository
2. **Create** a feature branch: `git checkout -b feature/amazing-feature`
3. **Make** your changes following the code style guidelines
4. **Add** tests for new functionality
5. **Update** documentation as needed
6. **Commit** your changes: `git commit -m 'Add amazing feature'`
7. **Push** to the branch: `git push origin feature/amazing-feature`
8. **Create** a Pull Request

### Pull Request Guidelines

- **Title**: Clear and descriptive
- **Description**: Explain what the PR does and why
- **Tests**: Include tests for new functionality
- **Documentation**: Update relevant documentation
- **Screenshots**: Include screenshots for UI changes

### Code Review Process

1. **Automated Checks**: CI/CD pipeline runs tests and style checks
2. **Review**: At least one maintainer must approve
3. **Merge**: Once approved, the PR can be merged

## Debugging

### Debug Build

```bash
cmake .. -DCMAKE_BUILD_TYPE=Debug
make
```

### Logging

The engine uses spdlog for logging:

```cpp
#include "core/Log.h"

// Log levels
Log::Trace("Detailed trace information");
Log::Debug("Debug information");
Log::Info("General information");
Log::Warning("Warning message");
Log::Error("Error message");
Log::Critical("Critical error");
```

### Profiling

The engine includes built-in profiling tools:

```cpp
// CPU profiling
NIMBUS_PROFILE_BEGIN("FunctionName");
// ... code ...
NIMBUS_PROFILE_END();

// GPU profiling
NIMBUS_GPU_PROFILE_BEGIN("RenderPass");
// ... rendering code ...
NIMBUS_GPU_PROFILE_END();
```

### Memory Debugging

```bash
# Use Valgrind (Linux)
valgrind --leak-check=full --show-leak-kinds=all ./NimbusEngine

# Use AddressSanitizer
cmake .. -DCMAKE_BUILD_TYPE=Debug -DSANITIZE_ADDRESS=ON
```

## Performance

### Optimization Guidelines

1. **Profile First**: Always profile before optimizing
2. **Cache Locality**: Keep related data together in memory
3. **Avoid Allocations**: Use object pools and pre-allocated buffers
4. **SIMD**: Use vectorized operations where possible
5. **Multi-threading**: Utilize the job system for parallel work

### Performance Tools

- **CPU Profiler**: Built-in profiler with hierarchical timing
- **GPU Profiler**: Vulkan/OpenGL performance analysis
- **Memory Profiler**: Allocation tracking and leak detection
- **Network Profiler**: Bandwidth and latency analysis

### Common Optimizations

```cpp
// Use object pools
class GameObjectPool {
    std::vector<std::unique_ptr<GameObject>> m_pool;
public:
    GameObject* Allocate();
    void Deallocate(GameObject* obj);
};

// Batch operations
void Renderer::RenderBatch(const std::vector<Mesh*>& meshes) {
    // Single draw call for multiple meshes
}

// Use SIMD for math operations
#include <immintrin.h>
__m256 result = _mm256_add_ps(a, b);
```

## Release Process

### Versioning

The engine uses semantic versioning (MAJOR.MINOR.PATCH):

- **MAJOR**: Breaking changes
- **MINOR**: New features, backward compatible
- **PATCH**: Bug fixes, backward compatible

### Release Checklist

1. **Update Version**: Update version in CMakeLists.txt and documentation
2. **Update Changelog**: Document all changes since last release
3. **Run Tests**: Ensure all tests pass
4. **Build Packages**: Create packages for all platforms
5. **Tag Release**: Create git tag for the release
6. **Upload Assets**: Upload packages to GitHub releases
7. **Update Documentation**: Update online documentation
8. **Announce**: Announce the release on social media and forums

### Package Creation

```bash
# Linux
./scripts/build.sh --package

# Windows
scripts\build.bat --package

# Arch Linux
makepkg -si
```

### Distribution

- **GitHub Releases**: Source code and binary packages
- **Package Managers**: 
  - Arch Linux: AUR package
  - Ubuntu/Debian: PPA repository
  - Windows: Chocolatey package
- **AppImage**: Portable Linux executable
- **Windows Installer**: NSIS-based installer

## Support

### Getting Help

- **Documentation**: Check the docs/ directory
- **Issues**: Report bugs on GitHub Issues
- **Discussions**: Ask questions on GitHub Discussions
- **Discord**: Join our community Discord server
- **Email**: Contact support@nimbus-engine.com

### Reporting Bugs

When reporting bugs, please include:

1. **Version**: Engine version and platform
2. **Steps**: Detailed steps to reproduce
3. **Expected**: What should happen
4. **Actual**: What actually happens
5. **Logs**: Relevant log output
6. **Screenshots**: If applicable

### Feature Requests

When requesting features, please include:

1. **Description**: Clear description of the feature
2. **Use Case**: How it would be used
3. **Priority**: High/Medium/Low
4. **Alternatives**: Any existing workarounds

---

Thank you for contributing to the Nimbus Engine project!