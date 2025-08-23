#pragma once

#include <memory>
#include <string>
#include <vector>
#include <functional>

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

namespace Nimbus {

    /**
     * @brief Main engine class that coordinates all subsystems
     * 
     * The Engine class is the central hub of the Nimbus Engine, managing
     * all subsystems including rendering, physics, audio, and the editor.
     * It provides a unified interface for game development and engine management.
     */
    class Engine {
    public:
        /**
         * @brief Engine configuration structure
         */
        struct Config {
            std::string appName = "Nimbus Engine Application";
            int windowWidth = 1280;
            int windowHeight = 720;
            bool enableEditor = true;
            bool enablePhysics = true;
            bool enableAudio = true;
            bool enableVulkan = true;
            bool enableOpenGL = true;
            bool enableDirectX = false;
            std::string assetPath = "assets/";
            std::string logPath = "logs/";
            bool enableDebugMode = false;
            bool enableProfiling = false;
        };

        /**
         * @brief Get the singleton instance of the engine
         * @return Reference to the engine instance
         */
        static Engine& GetInstance();

        /**
         * @brief Initialize the engine with the given configuration
         * @param config Engine configuration
         * @return True if initialization was successful
         */
        bool Initialize(const Config& config = Config{});

        /**
         * @brief Shutdown the engine and clean up resources
         */
        void Shutdown();

        /**
         * @brief Run the main engine loop
         * @return Exit code
         */
        int Run();

        /**
         * @brief Get the current engine configuration
         * @return Reference to the current configuration
         */
        const Config& GetConfig() const { return m_config; }

        /**
         * @brief Get the main application instance
         * @return Pointer to the application
         */
        Application* GetApplication() { return m_application.get(); }

        /**
         * @brief Get the active scene
         * @return Pointer to the active scene
         */
        Scene* GetActiveScene() { return m_activeScene.get(); }

        /**
         * @brief Set the active scene
         * @param scene Scene to set as active
         */
        void SetActiveScene(std::shared_ptr<Scene> scene);

        /**
         * @brief Load a scene from file
         * @param scenePath Path to the scene file
         * @return Pointer to the loaded scene
         */
        std::shared_ptr<Scene> LoadScene(const std::string& scenePath);

        /**
         * @brief Save the current scene to file
         * @param scenePath Path to save the scene to
         * @return True if save was successful
         */
        bool SaveScene(const std::string& scenePath);

        /**
         * @brief Get the rendering system
         * @return Pointer to the renderer
         */
        Renderer* GetRenderer() { return m_renderer.get(); }

        /**
         * @brief Get the physics engine
         * @return Pointer to the physics engine
         */
        PhysicsEngine* GetPhysicsEngine() { return m_physicsEngine.get(); }

        /**
         * @brief Get the audio engine
         * @return Pointer to the audio engine
         */
        AudioEngine* GetAudioEngine() { return m_audioEngine.get(); }

        /**
         * @brief Get the editor interface
         * @return Pointer to the editor
         */
        Editor* GetEditor() { return m_editor.get(); }

        /**
         * @brief Get the main window
         * @return Pointer to the window
         */
        Window* GetWindow() { return m_window.get(); }

        /**
         * @brief Get the input system
         * @return Pointer to the input system
         */
        Input* GetInput() { return m_input.get(); }

        /**
         * @brief Create a new GameObject
         * @param name Name of the GameObject
         * @return Pointer to the created GameObject
         */
        std::shared_ptr<GameObject> CreateGameObject(const std::string& name = "GameObject");

        /**
         * @brief Destroy a GameObject
         * @param gameObject GameObject to destroy
         */
        void DestroyGameObject(std::shared_ptr<GameObject> gameObject);

        /**
         * @brief Get all GameObjects in the active scene
         * @return Vector of GameObjects
         */
        std::vector<std::shared_ptr<GameObject>> GetAllGameObjects();

        /**
         * @brief Find a GameObject by name
         * @param name Name to search for
         * @return Pointer to the found GameObject, or nullptr if not found
         */
        std::shared_ptr<GameObject> FindGameObject(const std::string& name);

        /**
         * @brief Find GameObjects by tag
         * @param tag Tag to search for
         * @return Vector of GameObjects with the specified tag
         */
        std::vector<std::shared_ptr<GameObject>> FindGameObjectsByTag(const std::string& tag);

        /**
         * @brief Register a component type
         * @param componentType Type of component to register
         * @param createFunction Function to create the component
         */
        template<typename T>
        void RegisterComponentType() {
            m_componentRegistry[typeid(T).name()] = []() -> std::shared_ptr<Component> {
                return std::make_shared<T>();
            };
        }

        /**
         * @brief Create a component by type name
         * @param typeName Name of the component type
         * @return Pointer to the created component, or nullptr if type not found
         */
        std::shared_ptr<Component> CreateComponent(const std::string& typeName);

        /**
         * @brief Get the delta time since last frame
         * @return Delta time in seconds
         */
        float GetDeltaTime() const { return m_deltaTime; }

        /**
         * @brief Get the current frame rate
         * @return Frames per second
         */
        float GetFPS() const { return m_fps; }

        /**
         * @brief Check if the engine is running
         * @return True if the engine is running
         */
        bool IsRunning() const { return m_isRunning; }

        /**
         * @brief Check if the engine is in editor mode
         * @return True if in editor mode
         */
        bool IsEditorMode() const { return m_config.enableEditor; }

        /**
         * @brief Check if debug mode is enabled
         * @return True if debug mode is enabled
         */
        bool IsDebugMode() const { return m_config.enableDebugMode; }

        /**
         * @brief Log a message
         * @param level Log level
         * @param message Message to log
         */
        void Log(LogLevel level, const std::string& message);

        /**
         * @brief Get the asset path
         * @return Asset path string
         */
        const std::string& GetAssetPath() const { return m_config.assetPath; }

        /**
         * @brief Get the log path
         * @return Log path string
         */
        const std::string& GetLogPath() const { return m_config.logPath; }

    private:
        Engine() = default;
        ~Engine() = default;
        Engine(const Engine&) = delete;
        Engine& operator=(const Engine&) = delete;

        /**
         * @brief Initialize subsystems
         * @return True if all subsystems initialized successfully
         */
        bool InitializeSubsystems();

        /**
         * @brief Shutdown subsystems
         */
        void ShutdownSubsystems();

        /**
         * @brief Update the engine for one frame
         * @param deltaTime Time since last frame
         */
        void Update(float deltaTime);

        /**
         * @brief Render the current frame
         */
        void Render();

        /**
         * @brief Process input events
         */
        void ProcessInput();

        /**
         * @brief Update physics simulation
         * @param deltaTime Time since last frame
         */
        void UpdatePhysics(float deltaTime);

        /**
         * @brief Update audio system
         * @param deltaTime Time since last frame
         */
        void UpdateAudio(float deltaTime);

        // Engine configuration
        Config m_config;

        // Core systems
        std::unique_ptr<Application> m_application;
        std::shared_ptr<Scene> m_activeScene;
        std::unique_ptr<Renderer> m_renderer;
        std::unique_ptr<PhysicsEngine> m_physicsEngine;
        std::unique_ptr<AudioEngine> m_audioEngine;
        std::unique_ptr<Editor> m_editor;
        std::unique_ptr<Window> m_window;
        std::unique_ptr<Input> m_input;

        // Component registry
        std::unordered_map<std::string, std::function<std::shared_ptr<Component>()>> m_componentRegistry;

        // Timing
        float m_deltaTime = 0.0f;
        float m_fps = 0.0f;
        float m_lastFrameTime = 0.0f;
        int m_frameCount = 0;

        // State
        bool m_isRunning = false;
        bool m_isInitialized = false;
    };

    /**
     * @brief Convenience macro to get the engine instance
     */
    #define NIMBUS_ENGINE Nimbus::Engine::GetInstance()

} // namespace Nimbus