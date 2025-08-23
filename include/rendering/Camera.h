#pragma once

#include <glm/glm.hpp>

namespace Nimbus {

    /**
     * @brief Camera system for the Nimbus Engine
     * 
     * The Camera class represents a virtual camera and provides
     * projection and view matrix calculations.
     */
    class Camera {
    public:
        /**
         * @brief Constructor
         */
        Camera();

        /**
         * @brief Destructor
         */
        ~Camera();

        /**
         * @brief Check if this is the main camera
         * @return True if main camera
         */
        bool IsMainCamera() const { return m_isMainCamera; }

        /**
         * @brief Set main camera status
         * @param isMain True to set as main camera
         */
        void SetMainCamera(bool isMain) { m_isMainCamera = isMain; }

    private:
        bool m_isMainCamera = false;
    };

} // namespace Nimbus