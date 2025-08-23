#pragma once

#include <string>

namespace Nimbus {

    /**
     * @brief Texture system for the Nimbus Engine
     * 
     * The Texture class represents texture data and provides
     * texture management functionality.
     */
    class Texture {
    public:
        /**
         * @brief Constructor
         */
        Texture();

        /**
         * @brief Destructor
         */
        ~Texture();

        /**
         * @brief Get the texture name
         * @return Texture name
         */
        const std::string& GetName() const { return m_name; }

        /**
         * @brief Set the texture name
         * @param name New texture name
         */
        void SetName(const std::string& name) { m_name = name; }

        /**
         * @brief Get the texture width
         * @return Texture width
         */
        int GetWidth() const { return m_width; }

        /**
         * @brief Get the texture height
         * @return Texture height
         */
        int GetHeight() const { return m_height; }

    private:
        std::string m_name = "Texture";
        int m_width = 0;
        int m_height = 0;
    };

} // namespace Nimbus