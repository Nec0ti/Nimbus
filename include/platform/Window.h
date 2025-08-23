#pragma once

#include <string>

namespace Nimbus {

    /**
     * @brief Platform window abstraction
     * 
     * The Window class provides a cross-platform interface for window management,
     * handling window creation, input events, and rendering context.
     */
    class Window {
    public:
        /**
         * @brief Constructor
         */
        Window();

        /**
         * @brief Destructor
         */
        ~Window();

        /**
         * @brief Initialize the window
         * @param title Window title
         * @param width Window width
         * @param height Window height
         * @return True if initialization was successful
         */
        bool Initialize(const std::string& title, int width, int height);

        /**
         * @brief Shutdown the window
         */
        void Shutdown();

        /**
         * @brief Update the window
         */
        void Update();

        /**
         * @brief Check if the window should close
         * @return True if the window should close
         */
        bool ShouldClose() const { return m_shouldClose; }

        /**
         * @brief Get the window width
         * @return Window width
         */
        int GetWidth() const { return m_width; }

        /**
         * @brief Get the window height
         * @return Window height
         */
        int GetHeight() const { return m_height; }

        /**
         * @brief Resize the window
         * @param width New width
         * @param height New height
         */
        void Resize(int width, int height);

        /**
         * @brief Set the window title
         * @param title New title
         */
        void SetTitle(const std::string& title);

        /**
         * @brief Get the window title
         * @return Window title
         */
        const std::string& GetTitle() const { return m_title; }

        /**
         * @brief Set the window to fullscreen
         * @param fullscreen True to set fullscreen
         */
        void SetFullscreen(bool fullscreen);

        /**
         * @brief Check if the window is fullscreen
         * @return True if fullscreen
         */
        bool IsFullscreen() const { return m_fullscreen; }

        /**
         * @brief Set the window to vsync
         * @param vsync True to enable vsync
         */
        void SetVSync(bool vsync);

        /**
         * @brief Check if vsync is enabled
         * @return True if vsync is enabled
         */
        bool IsVSyncEnabled() const { return m_vsync; }

        /**
         * @brief Get the native window handle
         * @return Native window handle
         */
        void* GetNativeHandle() const { return m_nativeHandle; }

    private:
        std::string m_title;
        int m_width = 1280;
        int m_height = 720;
        bool m_shouldClose = false;
        bool m_fullscreen = false;
        bool m_vsync = true;
        void* m_nativeHandle = nullptr;
    };

} // namespace Nimbus