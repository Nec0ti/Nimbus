#pragma once

#include <memory>
#include <vector>
#include <unordered_map>
#include <string>

#include "rendering/RenderAPI.h"
#include "rendering/RenderPipeline.h"
#include "rendering/Material.h"
#include "rendering/Mesh.h"
#include "rendering/Texture.h"
#include "rendering/Shader.h"
#include "rendering/Camera.h"
#include "rendering/Light.h"
#include "core/Scene.h"

namespace Nimbus {

    class RenderAPI;
    class RenderPipeline;
    class Material;
    class Mesh;
    class Texture;
    class Shader;
    class Camera;
    class Light;
    class Scene;

    /**
     * @brief Main rendering system that manages the graphics pipeline
     * 
     * The Renderer class is responsible for managing the rendering pipeline,
     * coordinating between different rendering APIs (Vulkan, OpenGL, DirectX),
     * and providing a unified interface for rendering operations.
     */
    class Renderer {
    public:
        /**
         * @brief Rendering configuration
         */
        struct Config {
            int width = 1280;
            int height = 720;
            bool enableVSync = true;
            bool enableMSAA = true;
            int msaaSamples = 4;
            bool enableHDR = true;
            bool enableBloom = true;
            bool enableSSAO = true;
            bool enableSSR = true;
            bool enableTAA = true;
            std::string renderAPI = "Vulkan"; // "Vulkan", "OpenGL", "DirectX"
            std::string renderPipeline = "Forward+"; // "Forward+", "Deferred"
        };

        /**
         * @brief Constructor
         */
        Renderer();

        /**
         * @brief Destructor
         */
        ~Renderer();

        /**
         * @brief Initialize the renderer
         * @param config Rendering configuration
         * @return True if initialization was successful
         */
        bool Initialize(const Config& config = Config{});

        /**
         * @brief Shutdown the renderer
         */
        void Shutdown();

        /**
         * @brief Get the current configuration
         * @return Reference to the current configuration
         */
        const Config& GetConfig() const { return m_config; }

        /**
         * @brief Resize the render target
         * @param width New width
         * @param height New height
         */
        void Resize(int width, int height);

        /**
         * @brief Begin frame rendering
         */
        void BeginFrame();

        /**
         * @brief End frame rendering
         */
        void EndFrame();

        /**
         * @brief Render a scene
         * @param scene Scene to render
         * @param camera Camera to render from
         */
        void RenderScene(Scene* scene, Camera* camera);

        /**
         * @brief Render a mesh
         * @param mesh Mesh to render
         * @param material Material to use
         * @param transform Transform matrix
         */
        void RenderMesh(Mesh* mesh, Material* material, const glm::mat4& transform);

        /**
         * @brief Render a mesh with custom shader
         * @param mesh Mesh to render
         * @param shader Shader to use
         * @param transform Transform matrix
         */
        void RenderMesh(Mesh* mesh, Shader* shader, const glm::mat4& transform);

        /**
         * @brief Set the active camera
         * @param camera Camera to set as active
         */
        void SetActiveCamera(Camera* camera) { m_activeCamera = camera; }

        /**
         * @brief Get the active camera
         * @return Pointer to the active camera
         */
        Camera* GetActiveCamera() const { return m_activeCamera; }

        /**
         * @brief Add a light to the scene
         * @param light Light to add
         */
        void AddLight(Light* light);

        /**
         * @brief Remove a light from the scene
         * @param light Light to remove
         */
        void RemoveLight(Light* light);

        /**
         * @brief Get all lights in the scene
         * @return Vector of lights
         */
        const std::vector<Light*>& GetLights() const { return m_lights; }

        /**
         * @brief Clear all lights
         */
        void ClearLights() { m_lights.clear(); }

        /**
         * @brief Set the ambient light color
         * @param color Ambient light color
         */
        void SetAmbientLight(const glm::vec3& color) { m_ambientLight = color; }

        /**
         * @brief Get the ambient light color
         * @return Ambient light color
         */
        const glm::vec3& GetAmbientLight() const { return m_ambientLight; }

        /**
         * @brief Set the skybox texture
         * @param texture Skybox texture
         */
        void SetSkybox(Texture* texture) { m_skybox = texture; }

        /**
         * @brief Get the skybox texture
         * @return Pointer to the skybox texture
         */
        Texture* GetSkybox() const { return m_skybox; }

        /**
         * @brief Enable or disable wireframe mode
         * @param enabled True to enable wireframe mode
         */
        void SetWireframeMode(bool enabled) { m_wireframeMode = enabled; }

        /**
         * @brief Check if wireframe mode is enabled
         * @return True if wireframe mode is enabled
         */
        bool IsWireframeMode() const { return m_wireframeMode; }

        /**
         * @brief Set the clear color
         * @param color Clear color
         */
        void SetClearColor(const glm::vec4& color) { m_clearColor = color; }

        /**
         * @brief Get the clear color
         * @return Clear color
         */
        const glm::vec4& GetClearColor() const { return m_clearColor; }

        /**
         * @brief Get the render API
         * @return Pointer to the render API
         */
        RenderAPI* GetRenderAPI() const { return m_renderAPI.get(); }

        /**
         * @brief Get the render pipeline
         * @return Pointer to the render pipeline
         */
        RenderPipeline* GetRenderPipeline() const { return m_renderPipeline.get(); }

        /**
         * @brief Get the main render target
         * @return Pointer to the main render target
         */
        Texture* GetMainRenderTarget() const { return m_mainRenderTarget.get(); }

        /**
         * @brief Get the depth buffer
         * @return Pointer to the depth buffer
         */
        Texture* GetDepthBuffer() const { return m_depthBuffer.get(); }

        /**
         * @brief Get the normal buffer (for deferred rendering)
         * @return Pointer to the normal buffer
         */
        Texture* GetNormalBuffer() const { return m_normalBuffer.get(); }

        /**
         * @brief Get the albedo buffer (for deferred rendering)
         * @return Pointer to the albedo buffer
         */
        Texture* GetAlbedoBuffer() const { return m_albedoBuffer.get(); }

        /**
         * @brief Get the metallic-roughness buffer (for deferred rendering)
         * @return Pointer to the metallic-roughness buffer
         */
        Texture* GetMetallicRoughnessBuffer() const { return m_metallicRoughnessBuffer.get(); }

        /**
         * @brief Get the emissive buffer (for deferred rendering)
         * @return Pointer to the emissive buffer
         */
        Texture* GetEmissiveBuffer() const { return m_emissiveBuffer.get(); }

        /**
         * @brief Get the SSAO buffer
         * @return Pointer to the SSAO buffer
         */
        Texture* GetSSAOBuffer() const { return m_ssaoBuffer.get(); }

        /**
         * @brief Get the bloom buffer
         * @return Pointer to the bloom buffer
         */
        Texture* GetBloomBuffer() const { return m_bloomBuffer.get(); }

        /**
         * @brief Get the final render target
         * @return Pointer to the final render target
         */
        Texture* GetFinalRenderTarget() const { return m_finalRenderTarget.get(); }

        /**
         * @brief Get rendering statistics
         * @return Rendering statistics
         */
        struct RenderStats {
            int drawCalls = 0;
            int triangles = 0;
            int vertices = 0;
            int textures = 0;
            int shaders = 0;
            float frameTime = 0.0f;
            float gpuTime = 0.0f;
        };

        /**
         * @brief Get the current rendering statistics
         * @return Current rendering statistics
         */
        const RenderStats& GetRenderStats() const { return m_renderStats; }

        /**
         * @brief Reset rendering statistics
         */
        void ResetRenderStats();

        /**
         * @brief Enable or disable post-processing effects
         * @param effect Effect to toggle
         * @param enabled True to enable the effect
         */
        void SetPostProcessingEffect(const std::string& effect, bool enabled);

        /**
         * @brief Check if a post-processing effect is enabled
         * @param effect Effect to check
         * @return True if the effect is enabled
         */
        bool IsPostProcessingEffectEnabled(const std::string& effect) const;

        /**
         * @brief Set post-processing effect parameters
         * @param effect Effect name
         * @param params Effect parameters
         */
        void SetPostProcessingParams(const std::string& effect, const std::unordered_map<std::string, float>& params);

        /**
         * @brief Get post-processing effect parameters
         * @param effect Effect name
         * @return Effect parameters
         */
        std::unordered_map<std::string, float> GetPostProcessingParams(const std::string& effect) const;

        /**
         * @brief Take a screenshot
         * @param filepath Path to save the screenshot
         * @return True if screenshot was saved successfully
         */
        bool TakeScreenshot(const std::string& filepath);

        /**
         * @brief Begin GPU profiling
         * @param name Profile name
         */
        void BeginGPUProfile(const std::string& name);

        /**
         * @brief End GPU profiling
         */
        void EndGPUProfile();

    private:
        // Configuration
        Config m_config;

        // Core systems
        std::unique_ptr<RenderAPI> m_renderAPI;
        std::unique_ptr<RenderPipeline> m_renderPipeline;

        // Render targets
        std::unique_ptr<Texture> m_mainRenderTarget;
        std::unique_ptr<Texture> m_depthBuffer;
        std::unique_ptr<Texture> m_normalBuffer;
        std::unique_ptr<Texture> m_albedoBuffer;
        std::unique_ptr<Texture> m_metallicRoughnessBuffer;
        std::unique_ptr<Texture> m_emissiveBuffer;
        std::unique_ptr<Texture> m_ssaoBuffer;
        std::unique_ptr<Texture> m_bloomBuffer;
        std::unique_ptr<Texture> m_finalRenderTarget;

        // Scene data
        Camera* m_activeCamera = nullptr;
        std::vector<Light*> m_lights;
        glm::vec3 m_ambientLight = glm::vec3(0.1f);
        Texture* m_skybox = nullptr;

        // Rendering state
        bool m_wireframeMode = false;
        glm::vec4 m_clearColor = glm::vec4(0.2f, 0.3f, 0.4f, 1.0f);

        // Statistics
        RenderStats m_renderStats;

        // Post-processing
        std::unordered_map<std::string, bool> m_postProcessingEffects;
        std::unordered_map<std::string, std::unordered_map<std::string, float>> m_postProcessingParams;

        /**
         * @brief Create render targets
         * @return True if creation was successful
         */
        bool CreateRenderTargets();

        /**
         * @brief Destroy render targets
         */
        void DestroyRenderTargets();

        /**
         * @brief Update render targets for new size
         * @param width New width
         * @param height New height
         */
        void UpdateRenderTargets(int width, int height);

        /**
         * @brief Render the skybox
         */
        void RenderSkybox();

        /**
         * @brief Apply post-processing effects
         */
        void ApplyPostProcessing();

        /**
         * @brief Apply bloom effect
         */
        void ApplyBloom();

        /**
         * @brief Apply SSAO effect
         */
        void ApplySSAO();

        /**
         * @brief Apply tone mapping
         */
        void ApplyToneMapping();

        /**
         * @brief Apply anti-aliasing
         */
        void ApplyAntiAliasing();
    };

} // namespace Nimbus