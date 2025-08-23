#pragma once

#include <string>
#include <memory>

namespace Nimbus {

    class Shader;
    class Texture;

    /**
     * @brief Material system for the Nimbus Engine
     * 
     * The Material class defines the visual properties of rendered objects,
     * including shaders, textures, and material parameters.
     */
    class Material {
    public:
        /**
         * @brief Constructor
         */
        Material();

        /**
         * @brief Destructor
         */
        ~Material();

        /**
         * @brief Get the material name
         * @return Material name
         */
        const std::string& GetName() const { return m_name; }

        /**
         * @brief Set the material name
         * @param name New material name
         */
        void SetName(const std::string& name) { m_name = name; }

        /**
         * @brief Get the shader
         * @return Pointer to the shader
         */
        Shader* GetShader() const { return m_shader.get(); }

        /**
         * @brief Set the shader
         * @param shader New shader
         */
        void SetShader(std::shared_ptr<Shader> shader) { m_shader = shader; }

    private:
        std::string m_name = "Material";
        std::shared_ptr<Shader> m_shader;
    };

} // namespace Nimbus