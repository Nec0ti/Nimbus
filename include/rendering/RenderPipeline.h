#pragma once

#include <string>

namespace Nimbus {

    /**
     * @brief Rendering pipeline abstraction
     * 
     * The RenderPipeline class manages the rendering pipeline stages,
     * including forward, deferred, and custom rendering passes.
     */
    class RenderPipeline {
    public:
        /**
         * @brief Pipeline types
         */
        enum class Type {
            Forward,
            ForwardPlus,
            Deferred
        };

        /**
         * @brief Constructor
         */
        RenderPipeline();

        /**
         * @brief Destructor
         */
        ~RenderPipeline();

        /**
         * @brief Initialize the render pipeline
         * @param type Pipeline type to use
         * @return True if initialization was successful
         */
        bool Initialize(Type type);

        /**
         * @brief Shutdown the render pipeline
         */
        void Shutdown();

        /**
         * @brief Get the pipeline type
         * @return Current pipeline type
         */
        Type GetType() const { return m_type; }

        /**
         * @brief Get the pipeline name as string
         * @return Pipeline name
         */
        std::string GetTypeName() const;

        /**
         * @brief Check if the pipeline is initialized
         * @return True if initialized
         */
        bool IsInitialized() const { return m_initialized; }

    private:
        Type m_type = Type::ForwardPlus;
        bool m_initialized = false;
    };

} // namespace Nimbus