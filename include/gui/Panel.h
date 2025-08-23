#pragma once

#include <string>

namespace Nimbus {

    /**
     * @brief Base class for GUI panels
     * 
     * The Panel class provides the base functionality for all
     * editor panels in the Nimbus Engine GUI.
     */
    class Panel {
    public:
        /**
         * @brief Constructor
         * @param name Panel name
         */
        explicit Panel(const std::string& name = "Panel");

        /**
         * @brief Destructor
         */
        virtual ~Panel() = default;

        /**
         * @brief Get the panel name
         * @return Panel name
         */
        const std::string& GetName() const { return m_name; }

        /**
         * @brief Set the panel name
         * @param name New panel name
         */
        void SetName(const std::string& name) { m_name = name; }

        /**
         * @brief Check if the panel is visible
         * @return True if visible
         */
        bool IsVisible() const { return m_visible; }

        /**
         * @brief Set the panel visibility
         * @param visible New visibility state
         */
        void SetVisible(bool visible) { m_visible = visible; }

        /**
         * @brief Update the panel
         * @param deltaTime Time since last frame
         */
        virtual void Update(float deltaTime) {}

        /**
         * @brief Render the panel
         */
        virtual void Render() = 0;

    protected:
        std::string m_name;
        bool m_visible = true;
    };

} // namespace Nimbus