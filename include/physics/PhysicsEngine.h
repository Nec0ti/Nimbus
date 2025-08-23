#pragma once

namespace Nimbus {

    /**
     * @brief Physics engine for the Nimbus Engine
     * 
     * The PhysicsEngine class manages the physics simulation using
     * Bullet Physics and provides physics calculations.
     */
    class PhysicsEngine {
    public:
        /**
         * @brief Constructor
         */
        PhysicsEngine();

        /**
         * @brief Destructor
         */
        ~PhysicsEngine();

        /**
         * @brief Initialize the physics engine
         * @return True if initialization was successful
         */
        bool Initialize();

        /**
         * @brief Shutdown the physics engine
         */
        void Shutdown();

        /**
         * @brief Update the physics simulation
         * @param deltaTime Time since last frame
         */
        void Update(float deltaTime);

    private:
        bool m_initialized = false;
    };

} // namespace Nimbus