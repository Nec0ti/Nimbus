#pragma once

#include <glm/glm.hpp>

namespace Nimbus {

    /**
     * @brief Lighting system for the Nimbus Engine
     * 
     * The Light class represents various types of lights and provides
     * lighting calculations and parameters.
     */
    class Light {
    public:
        /**
         * @brief Light types
         */
        enum class Type {
            Directional,
            Point,
            Spot,
            Area
        };

        /**
         * @brief Constructor
         */
        Light();

        /**
         * @brief Destructor
         */
        ~Light();

        /**
         * @brief Get the light type
         * @return Light type
         */
        Type GetType() const { return m_type; }

        /**
         * @brief Set the light type
         * @param type New light type
         */
        void SetType(Type type) { m_type = type; }

    private:
        Type m_type = Type::Directional;
    };

} // namespace Nimbus