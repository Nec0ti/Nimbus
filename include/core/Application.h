#pragma once

#include <string>

namespace Nimbus {

    /**
     * @brief Application layer for the Nimbus Engine
     * 
     * The Application class provides the application-specific logic
     * and serves as a bridge between the engine and the specific game/app.
     */
    class Application {
    public:
        /**
         * @brief Constructor
         */
        Application();

        /**
         * @brief Destructor
         */
        ~Application();

        /**
         * @brief Initialize the application
         * @return True if initialization was successful
         */
        bool Initialize();

        /**
         * @brief Shutdown the application
         */
        void Shutdown();

        /**
         * @brief Update the application
         * @param deltaTime Time since last frame
         */
        void Update(float deltaTime);

        /**
         * @brief Get the application name
         * @return Application name
         */
        const std::string& GetName() const { return m_name; }

        /**
         * @brief Set the application name
         * @param name New application name
         */
        void SetName(const std::string& name) { m_name = name; }

    private:
        std::string m_name = "Nimbus Application";
    };

} // namespace Nimbus