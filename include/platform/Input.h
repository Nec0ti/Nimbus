#pragma once

#include <unordered_map>

namespace Nimbus {

    class Window;

    /**
     * @brief Input system for the Nimbus Engine
     * 
     * The Input class provides a cross-platform interface for handling
     * keyboard, mouse, and gamepad input.
     */
    class Input {
    public:
        /**
         * @brief Key codes
         */
        enum class Key {
            Unknown = -1,
            Space = 32,
            Apostrophe = 39,
            Comma = 44,
            Minus = 45,
            Period = 46,
            Slash = 47,
            Key0 = 48, Key1, Key2, Key3, Key4, Key5, Key6, Key7, Key8, Key9,
            Semicolon = 59,
            Equal = 61,
            A = 65, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z,
            LeftBracket = 91,
            Backslash = 92,
            RightBracket = 93,
            GraveAccent = 96,
            Escape = 256,
            Enter, Tab, Right, Left, Down, Up,
            PageUp, PageDown, Home, End,
            Insert = 260, Delete,
            RightShift = 344, LeftShift,
            RightControl = 346, LeftControl,
            RightAlt = 348, LeftAlt,
            RightSuper = 347, LeftSuper,
            Menu = 348,
            F1 = 290, F2, F3, F4, F5, F6, F7, F8, F9, F10, F11, F12,
            NumLock = 280,
            ScrollLock = 281,
            CapsLock = 282
        };

        /**
         * @brief Mouse button codes
         */
        enum class MouseButton {
            Left = 0,
            Right = 1,
            Middle = 2,
            Button4 = 3,
            Button5 = 4,
            Button6 = 5,
            Button7 = 6,
            Button8 = 7
        };

        /**
         * @brief Constructor
         */
        Input();

        /**
         * @brief Destructor
         */
        ~Input();

        /**
         * @brief Initialize the input system
         * @param window Window to get input from
         * @return True if initialization was successful
         */
        bool Initialize(Window* window);

        /**
         * @brief Shutdown the input system
         */
        void Shutdown();

        /**
         * @brief Update the input system
         */
        void Update();

        /**
         * @brief Check if a key is pressed
         * @param key Key to check
         * @return True if the key is pressed
         */
        bool IsKeyPressed(Key key) const;

        /**
         * @brief Check if a key was just pressed this frame
         * @param key Key to check
         * @return True if the key was just pressed
         */
        bool IsKeyJustPressed(Key key) const;

        /**
         * @brief Check if a key was just released this frame
         * @param key Key to check
         * @return True if the key was just released
         */
        bool IsKeyJustReleased(Key key) const;

        /**
         * @brief Check if a mouse button is pressed
         * @param button Mouse button to check
         * @return True if the button is pressed
         */
        bool IsMouseButtonPressed(MouseButton button) const;

        /**
         * @brief Check if a mouse button was just pressed this frame
         * @param button Mouse button to check
         * @return True if the button was just pressed
         */
        bool IsMouseButtonJustPressed(MouseButton button) const;

        /**
         * @brief Check if a mouse button was just released this frame
         * @param button Mouse button to check
         * @return True if the button was just released
         */
        bool IsMouseButtonJustReleased(MouseButton button) const;

        /**
         * @brief Get the mouse position
         * @return Mouse position (x, y)
         */
        std::pair<double, double> GetMousePosition() const;

        /**
         * @brief Get the mouse delta (movement since last frame)
         * @return Mouse delta (x, y)
         */
        std::pair<double, double> GetMouseDelta() const;

        /**
         * @brief Get the mouse scroll delta
         * @return Mouse scroll delta (x, y)
         */
        std::pair<double, double> GetMouseScrollDelta() const;

        /**
         * @brief Set the mouse position
         * @param x X coordinate
         * @param y Y coordinate
         */
        void SetMousePosition(double x, double y);

        /**
         * @brief Set the mouse cursor mode
         * @param mode Cursor mode
         */
        enum class CursorMode {
            Normal,
            Hidden,
            Disabled
        };

        void SetCursorMode(CursorMode mode);

        /**
         * @brief Get the cursor mode
         * @return Current cursor mode
         */
        CursorMode GetCursorMode() const { return m_cursorMode; }

        /**
         * @brief Check if any key is pressed
         * @return True if any key is pressed
         */
        bool IsAnyKeyPressed() const;

        /**
         * @brief Check if any mouse button is pressed
         * @return True if any mouse button is pressed
         */
        bool IsAnyMouseButtonPressed() const;

        /**
         * @brief Get the text input buffer
         * @return Text input buffer
         */
        const std::string& GetTextInput() const { return m_textInput; }

        /**
         * @brief Clear the text input buffer
         */
        void ClearTextInput() { m_textInput.clear(); }

    private:
        Window* m_window = nullptr;
        CursorMode m_cursorMode = CursorMode::Normal;

        std::unordered_map<Key, bool> m_keyStates;
        std::unordered_map<Key, bool> m_previousKeyStates;
        std::unordered_map<MouseButton, bool> m_mouseButtonStates;
        std::unordered_map<MouseButton, bool> m_previousMouseButtonStates;

        double m_mouseX = 0.0;
        double m_mouseY = 0.0;
        double m_previousMouseX = 0.0;
        double m_previousMouseY = 0.0;
        double m_mouseScrollX = 0.0;
        double m_mouseScrollY = 0.0;

        std::string m_textInput;
    };

} // namespace Nimbus