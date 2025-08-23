#pragma once

#include <string>

namespace Nimbus {

    /**
     * @brief Graphics API abstraction layer
     * 
     * The RenderAPI class provides a unified interface for different
     * graphics APIs (Vulkan, OpenGL, DirectX) and manages the
     * rendering context and device.
     */
    class RenderAPI {
    public:
        /**
         * @brief Graphics API types
         */
        enum class Type {
            Vulkan,
            OpenGL,
            DirectX12
        };

        /**
         * @brief Constructor
         */
        RenderAPI();

        /**
         * @brief Destructor
         */
        ~RenderAPI();

        /**
         * @brief Initialize the render API
         * @param type API type to use
         * @return True if initialization was successful
         */
        bool Initialize(Type type);

        /**
         * @brief Shutdown the render API
         */
        void Shutdown();

        /**
         * @brief Get the API type
         * @return Current API type
         */
        Type GetType() const { return m_type; }

        /**
         * @brief Get the API name as string
         * @return API name
         */
        std::string GetTypeName() const;

        /**
         * @brief Check if the API is initialized
         * @return True if initialized
         */
        bool IsInitialized() const { return m_initialized; }

    private:
        Type m_type = Type::Vulkan;
        bool m_initialized = false;
    };

} // namespace Nimbus