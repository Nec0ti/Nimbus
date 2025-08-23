#pragma once

#include <string>

namespace Nimbus {

    /**
     * @brief Shader system for the Nimbus Engine
     * 
     * The Shader class represents GPU shader programs and provides
     * shader compilation and management functionality.
     */
    class Shader {
    public:
        /**
         * @brief Constructor
         */
        Shader();

        /**
         * @brief Destructor
         */
        ~Shader();

        /**
         * @brief Get the shader name
         * @return Shader name
         */
        const std::string& GetName() const { return m_name; }

        /**
         * @brief Set the shader name
         * @param name New shader name
         */
        void SetName(const std::string& name) { m_name = name; }

    private:
        std::string m_name = "Shader";
    };

} // namespace Nimbus