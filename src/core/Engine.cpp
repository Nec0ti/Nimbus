#include "nimbus/Engine.h"
#include "core/Application.h"
#include "core/Scene.h"
#include "core/GameObject.h"
#include "core/Component.h"
#include "rendering/Renderer.h"
#include "physics/PhysicsEngine.h"
#include "audio/AudioEngine.h"
#include "gui/Editor.h"
#include "platform/Window.h"
#include "platform/Input.h"
#include "core/Log.h"

#include <chrono>
#include <thread>
#include <algorithm>

namespace Nimbus {

    Engine& Engine::GetInstance() {
        static Engine instance;
        return instance;
    }

    bool Engine::Initialize(const Config& config) {
        if (m_isInitialized) {
            Log::Warning("Engine already initialized");
            return true;
        }

        m_config = config;
        Log::Info("Initializing Nimbus Engine v1.0.0");

        // Initialize subsystems
        if (!InitializeSubsystems()) {
            Log::Error("Failed to initialize engine subsystems");
            return false;
        }

        // Register default component types
        RegisterComponentTypes();

        // Create default scene
        m_activeScene = std::make_shared<Scene>("Default Scene");
        m_activeScene->Initialize();

        m_isInitialized = true;
        Log::Info("Nimbus Engine initialized successfully");
        return true;
    }

    void Engine::Shutdown() {
        if (!m_isInitialized) {
            return;
        }

        Log::Info("Shutting down Nimbus Engine");

        // Shutdown subsystems
        ShutdownSubsystems();

        m_isInitialized = false;
        m_isRunning = false;
        Log::Info("Nimbus Engine shutdown complete");
    }

    int Engine::Run() {
        if (!m_isInitialized) {
            Log::Error("Engine not initialized");
            return -1;
        }

        m_isRunning = true;
        Log::Info("Starting engine main loop");

        auto lastFrameTime = std::chrono::high_resolution_clock::now();

        while (m_isRunning) {
            auto currentFrameTime = std::chrono::high_resolution_clock::now();
            auto deltaTime = std::chrono::duration<float>(currentFrameTime - lastFrameTime).count();
            lastFrameTime = currentFrameTime;

            // Cap delta time to prevent spiral of death
            deltaTime = std::min(deltaTime, 1.0f / 30.0f);

            m_deltaTime = deltaTime;
            m_frameCount++;

            // Update FPS calculation
            static float fpsTimer = 0.0f;
            fpsTimer += deltaTime;
            if (fpsTimer >= 1.0f) {
                m_fps = static_cast<float>(m_frameCount) / fpsTimer;
                m_frameCount = 0;
                fpsTimer = 0.0f;
            }

            // Process input
            ProcessInput();

            // Update engine
            Update(deltaTime);

            // Render frame
            Render();

            // Update window
            if (m_window) {
                m_window->Update();
                if (m_window->ShouldClose()) {
                    m_isRunning = false;
                }
            }
        }

        Log::Info("Engine main loop ended");
        return 0;
    }

    void Engine::SetActiveScene(std::shared_ptr<Scene> scene) {
        if (m_activeScene) {
            m_activeScene->OnDeactivate();
        }

        m_activeScene = scene;

        if (m_activeScene) {
            m_activeScene->OnActivate();
        }

        // Update editor
        if (m_editor) {
            m_editor->SetActiveScene(m_activeScene.get());
        }
    }

    std::shared_ptr<Scene> Engine::LoadScene(const std::string& scenePath) {
        // TODO: Implement scene loading from file
        Log::Info("Loading scene: {}", scenePath);
        
        auto scene = std::make_shared<Scene>("Loaded Scene");
        scene->Initialize();
        
        SetActiveScene(scene);
        return scene;
    }

    bool Engine::SaveScene(const std::string& scenePath) {
        if (!m_activeScene) {
            Log::Warning("No active scene to save");
            return false;
        }

        // TODO: Implement scene saving to file
        Log::Info("Saving scene: {}", scenePath);
        return true;
    }

    std::shared_ptr<GameObject> Engine::CreateGameObject(const std::string& name) {
        if (!m_activeScene) {
            Log::Warning("No active scene to create GameObject in");
            return nullptr;
        }

        auto gameObject = std::make_shared<GameObject>(name);
        gameObject->SetScene(m_activeScene.get());
        m_activeScene->AddGameObject(gameObject);
        
        Log::Debug("Created GameObject: {}", name);
        return gameObject;
    }

    void Engine::DestroyGameObject(std::shared_ptr<GameObject> gameObject) {
        if (!gameObject) {
            return;
        }

        if (m_activeScene) {
            m_activeScene->RemoveGameObject(gameObject);
        }

        Log::Debug("Destroyed GameObject: {}", gameObject->GetName());
    }

    std::vector<std::shared_ptr<GameObject>> Engine::GetAllGameObjects() {
        if (!m_activeScene) {
            return {};
        }
        return m_activeScene->GetGameObjects();
    }

    std::shared_ptr<GameObject> Engine::FindGameObject(const std::string& name) {
        if (!m_activeScene) {
            return nullptr;
        }
        return m_activeScene->FindGameObject(name);
    }

    std::vector<std::shared_ptr<GameObject>> Engine::FindGameObjectsByTag(const std::string& tag) {
        if (!m_activeScene) {
            return {};
        }
        return m_activeScene->FindGameObjectsByTag(tag);
    }

    std::shared_ptr<Component> Engine::CreateComponent(const std::string& typeName) {
        auto it = m_componentRegistry.find(typeName);
        if (it != m_componentRegistry.end()) {
            return it->second();
        }
        
        Log::Warning("Unknown component type: {}", typeName);
        return nullptr;
    }

    void Engine::Log(LogLevel level, const std::string& message) {
        Nimbus::Log::Log(level, message);
    }

    bool Engine::InitializeSubsystems() {
        Log::Info("Initializing engine subsystems");

        // Initialize window
        m_window = std::make_unique<Window>();
        if (!m_window->Initialize(m_config.appName, m_config.windowWidth, m_config.windowHeight)) {
            Log::Error("Failed to initialize window");
            return false;
        }

        // Initialize input system
        m_input = std::make_unique<Input>();
        if (!m_input->Initialize(m_window.get())) {
            Log::Error("Failed to initialize input system");
            return false;
        }

        // Initialize renderer
        Renderer::Config rendererConfig;
        rendererConfig.width = m_config.windowWidth;
        rendererConfig.height = m_config.windowHeight;
        rendererConfig.renderAPI = m_config.enableVulkan ? "Vulkan" : "OpenGL";
        
        m_renderer = std::make_unique<Renderer>();
        if (!m_renderer->Initialize(rendererConfig)) {
            Log::Error("Failed to initialize renderer");
            return false;
        }

        // Initialize physics engine
        if (m_config.enablePhysics) {
            m_physicsEngine = std::make_unique<PhysicsEngine>();
            if (!m_physicsEngine->Initialize()) {
                Log::Error("Failed to initialize physics engine");
                return false;
            }
        }

        // Initialize audio engine
        if (m_config.enableAudio) {
            m_audioEngine = std::make_unique<AudioEngine>();
            if (!m_audioEngine->Initialize()) {
                Log::Error("Failed to initialize audio engine");
                return false;
            }
        }

        // Initialize editor
        if (m_config.enableEditor) {
            Editor::Config editorConfig;
            editorConfig.width = m_config.windowWidth;
            editorConfig.height = m_config.windowHeight;
            editorConfig.title = m_config.appName;
            
            m_editor = std::make_unique<Editor>();
            if (!m_editor->Initialize(editorConfig)) {
                Log::Error("Failed to initialize editor");
                return false;
            }
        }

        // Initialize application
        m_application = std::make_unique<Application>();
        if (!m_application->Initialize()) {
            Log::Error("Failed to initialize application");
            return false;
        }

        Log::Info("All subsystems initialized successfully");
        return true;
    }

    void Engine::ShutdownSubsystems() {
        Log::Info("Shutting down engine subsystems");

        if (m_application) {
            m_application->Shutdown();
        }

        if (m_editor) {
            m_editor->Shutdown();
        }

        if (m_audioEngine) {
            m_audioEngine->Shutdown();
        }

        if (m_physicsEngine) {
            m_physicsEngine->Shutdown();
        }

        if (m_renderer) {
            m_renderer->Shutdown();
        }

        if (m_input) {
            m_input->Shutdown();
        }

        if (m_window) {
            m_window->Shutdown();
        }

        Log::Info("All subsystems shut down successfully");
    }

    void Engine::Update(float deltaTime) {
        // Update application
        if (m_application) {
            m_application->Update(deltaTime);
        }

        // Update active scene
        if (m_activeScene) {
            m_activeScene->Update(deltaTime);
        }

        // Update physics
        UpdatePhysics(deltaTime);

        // Update audio
        UpdateAudio(deltaTime);

        // Update editor
        if (m_editor) {
            m_editor->Update(deltaTime);
        }
    }

    void Engine::Render() {
        if (!m_renderer) {
            return;
        }

        m_renderer->BeginFrame();

        // Render scene
        if (m_activeScene) {
            // Find main camera
            Camera* mainCamera = nullptr;
            auto gameObjects = m_activeScene->GetGameObjects();
            for (const auto& gameObject : gameObjects) {
                if (auto camera = gameObject->GetComponent<Camera>()) {
                    if (camera->IsMainCamera()) {
                        mainCamera = camera;
                        break;
                    }
                }
            }

            if (mainCamera) {
                m_renderer->RenderScene(m_activeScene.get(), mainCamera);
            }
        }

        // Render editor
        if (m_editor) {
            m_editor->Render();
        }

        m_renderer->EndFrame();
    }

    void Engine::ProcessInput() {
        if (m_input) {
            m_input->Update();
        }
    }

    void Engine::UpdatePhysics(float deltaTime) {
        if (m_physicsEngine && m_activeScene) {
            m_physicsEngine->Update(deltaTime);
        }
    }

    void Engine::UpdateAudio(float deltaTime) {
        if (m_audioEngine && m_activeScene) {
            m_audioEngine->Update(deltaTime);
        }
    }

    void Engine::RegisterComponentTypes() {
        // Register built-in component types
        // This will be expanded as more components are implemented
        
        Log::Info("Registering component types");
        
        // TODO: Register all component types here
        // RegisterComponentType<Transform>();
        // RegisterComponentType<MeshRenderer>();
        // RegisterComponentType<Camera>();
        // RegisterComponentType<Light>();
        // etc.
    }

} // namespace Nimbus