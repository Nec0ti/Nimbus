#include "nimbus/Engine.h"
#include "core/Log.h"

#include <iostream>
#include <memory>

int main(int argc, char* argv[]) {
    // Initialize logging
    Nimbus::Log::Initialize();
    
    Nimbus::Log::Info("Starting Nimbus Engine Editor");
    Nimbus::Log::Info("Version: 1.0.0");
    Nimbus::Log::Info("Build: 2024.3.1");

    try {
        // Configure the engine
        Nimbus::Engine::Config config;
        config.appName = "Nimbus Engine Editor";
        config.windowWidth = 1920;
        config.windowHeight = 1080;
        config.enableEditor = true;
        config.enablePhysics = true;
        config.enableAudio = true;
        config.enableVulkan = true;
        config.enableOpenGL = true;
        config.enableDirectX = false;
        config.assetPath = "assets/";
        config.logPath = "logs/";
        config.enableDebugMode = true;
        config.enableProfiling = true;

        // Initialize the engine
        auto& engine = Nimbus::Engine::GetInstance();
        if (!engine.Initialize(config)) {
            Nimbus::Log::Error("Failed to initialize Nimbus Engine");
            return -1;
        }

        // Create a sample scene
        auto scene = engine.GetActiveScene();
        if (scene) {
            // Create a main camera
            auto camera = engine.CreateGameObject("Main Camera");
            if (camera) {
                // TODO: Add Camera component
                Nimbus::Log::Info("Created main camera");
            }

            // Create a directional light
            auto light = engine.CreateGameObject("Directional Light");
            if (light) {
                // TODO: Add Light component
                Nimbus::Log::Info("Created directional light");
            }

            // Create a sample cube
            auto cube = engine.CreateGameObject("Cube");
            if (cube) {
                // TODO: Add MeshRenderer component with cube mesh
                Nimbus::Log::Info("Created sample cube");
            }

            // Create a sample sphere
            auto sphere = engine.CreateGameObject("Sphere");
            if (sphere) {
                // TODO: Add MeshRenderer component with sphere mesh
                Nimbus::Log::Info("Created sample sphere");
            }

            // Create a ground plane
            auto plane = engine.CreateGameObject("Ground");
            if (plane) {
                // TODO: Add MeshRenderer component with plane mesh
                Nimbus::Log::Info("Created ground plane");
            }
        }

        // Run the engine
        int exitCode = engine.Run();

        // Shutdown the engine
        engine.Shutdown();

        Nimbus::Log::Info("Nimbus Engine Editor shutdown complete");
        return exitCode;

    } catch (const std::exception& e) {
        Nimbus::Log::Error("Unhandled exception: {}", e.what());
        std::cerr << "Unhandled exception: " << e.what() << std::endl;
        return -1;
    } catch (...) {
        Nimbus::Log::Error("Unknown unhandled exception");
        std::cerr << "Unknown unhandled exception" << std::endl;
        return -1;
    }
}