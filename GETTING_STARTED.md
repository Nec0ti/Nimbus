# Getting Started with Nimbus Engine

Welcome to Nimbus Engine! This guide will help you get up and running with your first 3D game project.

## 🚀 Quick Setup

### 1. Build the Engine

#### Linux (Ubuntu/Debian/Arch)
```bash
# Clone the repository
git clone --recursive https://github.com/NimbusEngine/NimbusEngine.git
cd NimbusEngine

# Install dependencies and build (automated)
./build.sh --install-deps

# Or build manually
mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
make -j$(nproc)
```

#### Windows
```cmd
# Clone the repository
git clone --recursive https://github.com/NimbusEngine/NimbusEngine.git
cd NimbusEngine

# Generate Visual Studio solution
mkdir build && cd build
cmake .. -G "Visual Studio 16 2019" -A x64

# Build with Visual Studio or command line
cmake --build . --config Release
```

### 2. Launch the Editor

```bash
# From the build directory
./bin/NimbusEditor
```

## 🎮 Your First Game

### Creating a New Project

1. **Launch Nimbus Editor**
   - The editor starts with a default empty scene
   - Familiarize yourself with the Unity-style interface

2. **Scene Layout Overview**
   - **Hierarchy Panel** (left): Shows all GameObjects in your scene
   - **Scene View** (center): 3D viewport for editing your scene
   - **Inspector Panel** (right): Edit properties of selected objects
   - **Project Browser** (bottom): Manage assets and files
   - **Console** (bottom): View logs and errors

### Adding Your First GameObject

1. **Create a Cube**
   ```
   Right-click in Hierarchy → 3D Object → Cube
   ```

2. **Position the Cube**
   - Select the cube in the hierarchy
   - In the Inspector, modify Transform component:
     - Position: (0, 1, 0)
     - Rotation: (0, 45, 0)
     - Scale: (1, 1, 1)

3. **Add a Camera**
   ```
   Right-click in Hierarchy → Camera
   ```
   - Position: (0, 2, -5)
   - Look at: (0, 0, 0)

### Creating Materials

1. **Create a Material**
   ```
   Right-click in Project Browser → Create → Material
   ```

2. **Assign to Cube**
   - Select the cube
   - Drag the material to the Mesh Renderer component
   - Adjust material properties in Inspector

### Adding Lighting

1. **Directional Light**
   ```
   Right-click in Hierarchy → Light → Directional Light
   ```
   - Rotation: (45, 30, 0) for nice shadows

2. **Configure Shadows**
   - Select the light
   - Enable shadows in Inspector
   - Adjust shadow distance and quality

## 🛠️ Scripting Your Game

### C++ Components (Advanced)

Create custom components by inheriting from base classes:

```cpp
// PlayerController.h
#include <Nimbus.h>

class PlayerController : public Nimbus::Component
{
public:
    void OnUpdate(Nimbus::Timestep ts) override;
    void OnEvent(Nimbus::Event& e) override;

private:
    float m_Speed = 5.0f;
    Nimbus::Entity m_Entity;
};

// PlayerController.cpp
void PlayerController::OnUpdate(Nimbus::Timestep ts)
{
    auto& transform = m_Entity.GetComponent<Nimbus::TransformComponent>();
    
    float speed = m_Speed * ts;
    
    if (Nimbus::Input::IsKeyPressed(Nimbus::Key::W))
        transform.Translation.z += speed;
    if (Nimbus::Input::IsKeyPressed(Nimbus::Key::S))
        transform.Translation.z -= speed;
    if (Nimbus::Input::IsKeyPressed(Nimbus::Key::A))
        transform.Translation.x -= speed;
    if (Nimbus::Input::IsKeyPressed(Nimbus::Key::D))
        transform.Translation.x += speed;
}
```

### C# Scripting (Coming Soon)

The engine is designed to support Unity-compatible C# scripts:

```csharp
using Nimbus;

public class PlayerController : MonoBehaviour
{
    public float speed = 5.0f;
    
    void Update()
    {
        float horizontal = Input.GetAxis("Horizontal");
        float vertical = Input.GetAxis("Vertical");
        
        Vector3 movement = new Vector3(horizontal, 0, vertical) * speed * Time.deltaTime;
        transform.Translate(movement);
    }
}
```

## 🎨 Asset Workflow

### Importing 3D Models

1. **Supported Formats**: FBX, OBJ, DAE, 3DS, BLEND
2. **Import Process**:
   - Drag model files to Project Browser
   - Adjust import settings in Inspector
   - Models automatically generate materials and textures

### Texture Import

1. **Supported Formats**: PNG, JPG, TGA, DDS, EXR, HDR
2. **Compression Settings**:
   - Automatic compression based on usage
   - Manual override in import settings

### Audio Assets

1. **Supported Formats**: WAV, MP3, OGG, FLAC
2. **3D Audio Support**:
   - Spatial audio with distance attenuation
   - Reverb zones and audio mixing

## 🎯 Building Your Game

### Build Settings

1. **Access Build Settings**
   ```
   File → Build Settings
   ```

2. **Configure Platform**
   - **Windows**: Creates .exe with dependencies
   - **Linux**: Creates native executable
   - **Arch Linux**: Creates .pkg.tar.xz package

3. **Build Process**
   ```bash
   # Command line build
   cmake --build . --target package
   
   # Or use the build script
   ./build.sh --package
   ```

### Deployment

#### Windows Distribution
```bash
# Creates installer
NimbusEngine-1.0.0-win64.exe
```

#### Linux Distribution
```bash
# Arch Linux package
sudo pacman -U nimbusengine-1.0.0-x86_64.pkg.tar.xz

# Generic Linux
tar -xzf nimbusengine-1.0.0-linux.tar.gz
cd nimbusengine
./install.sh
```

## 🚀 Advanced Features

### Performance Optimization

1. **LOD System**
   - Automatic level-of-detail for meshes
   - Distance-based quality scaling

2. **Occlusion Culling**
   - Hardware occlusion queries
   - Hierarchical Z-buffer culling

3. **Batching**
   - Dynamic batching for similar objects
   - GPU instancing for identical objects

### Rendering Pipeline

1. **Forward+ Rendering**
   - Tiled forward rendering for many lights
   - Automatic fallback to deferred rendering

2. **PBR Materials**
   - Physically based shading
   - Metallic/Roughness workflow
   - Image-based lighting

3. **Post-Processing**
   - Bloom, tone mapping, color grading
   - Screen-space ambient occlusion
   - Temporal anti-aliasing

### Physics Integration

1. **Bullet Physics**
   - Rigid body dynamics
   - Collision detection
   - Constraint solving

2. **Component Setup**
   ```cpp
   entity.AddComponent<RigidBodyComponent>();
   entity.AddComponent<BoxColliderComponent>();
   ```

## 🛠️ Editor Extensions

### Custom Inspector

Create custom property editors:

```cpp
class CustomInspector : public Nimbus::ComponentInspector<MyComponent>
{
public:
    void OnInspectorGUI() override
    {
        ImGui::Text("Custom Component");
        ImGui::SliderFloat("Speed", &component.speed, 0.0f, 10.0f);
        ImGui::ColorEdit3("Color", glm::value_ptr(component.color));
    }
};
```

### Editor Tools

Add custom menu items and tools:

```cpp
NIMBUS_EDITOR_MENU("Tools/My Tool")
void MyCustomTool()
{
    // Custom tool implementation
}
```

## 📚 Learning Resources

### Tutorials
- **Basic 3D Scene**: Learn the fundamentals
- **Character Controller**: Create a player character
- **Level Design**: Build environments
- **Particle Effects**: Add visual flair

### API Reference
- **[Core Classes](docs/api/core.md)**: Application, Scene, Entity
- **[Rendering](docs/api/rendering.md)**: Renderer, Materials, Lighting
- **[Physics](docs/api/physics.md)**: RigidBody, Colliders, Constraints
- **[Audio](docs/api/audio.md)**: AudioSource, 3D positioning

### Community
- **Discord**: [discord.gg/nimbusengine](https://discord.gg/nimbusengine)
- **Forum**: [forum.nimbusengine.com](https://forum.nimbusengine.com)
- **YouTube**: [youtube.com/nimbusengine](https://youtube.com/nimbusengine)

## 🐛 Troubleshooting

### Common Issues

1. **Build Fails**
   ```bash
   # Check dependencies
   ./build.sh --install-deps
   
   # Clean rebuild
   ./build.sh --clean
   ```

2. **Editor Won't Start**
   ```bash
   # Check OpenGL support
   glxinfo | grep "OpenGL version"
   
   # Run with debug output
   ./bin/NimbusEditor --verbose
   ```

3. **Performance Issues**
   - Enable GPU profiling in Editor
   - Check draw call count in Stats panel
   - Optimize materials and textures

### Getting Help

1. **Check Logs**
   - Console panel in editor
   - Log files in `~/.config/NimbusEngine/logs/`

2. **Report Issues**
   - GitHub Issues: [github.com/NimbusEngine/NimbusEngine/issues](https://github.com/NimbusEngine/NimbusEngine/issues)
   - Include system info and reproduction steps

3. **Community Support**
   - Ask questions on Discord or Forum
   - Share screenshots and project files

## 🎉 Next Steps

Congratulations! You now have the basics to start creating with Nimbus Engine. Here's what to explore next:

1. **Follow Tutorials**: Complete the official tutorial series
2. **Join Community**: Connect with other developers
3. **Read Documentation**: Deep dive into advanced features
4. **Create Games**: Start building your dream project!

Happy game development! 🎮✨