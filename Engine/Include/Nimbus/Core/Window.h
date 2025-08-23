#pragma once

#include "Nimbus/Core/Base.h"
#include "Nimbus/Events/Event.h"

struct GLFWwindow;

namespace Nimbus {

    struct WindowProps
    {
        std::string Title;
        uint32 Width;
        uint32 Height;

        WindowProps(const std::string& title = "Nimbus Engine",
                   uint32 width = 1600,
                   uint32 height = 900)
            : Title(title), Width(width), Height(height)
        {
        }
    };

    // Interface representing a desktop system based Window
    class NIMBUS_API Window
    {
    public:
        using EventCallbackFn = std::function<void(Event&)>;

        virtual ~Window() = default;

        virtual void OnUpdate() = 0;

        virtual uint32 GetWidth() const = 0;
        virtual uint32 GetHeight() const = 0;

        // Window attributes
        virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
        virtual void SetVSync(bool enabled) = 0;
        virtual bool IsVSync() const = 0;

        virtual void* GetNativeWindow() const = 0;

        static Scope<Window> Create(const WindowProps& props = WindowProps());
    };

    // Platform-specific Window implementation
    class NIMBUS_API WindowsWindow : public Window
    {
    public:
        WindowsWindow(const WindowProps& props);
        virtual ~WindowsWindow();

        void OnUpdate() override;

        uint32 GetWidth() const override { return m_Data.Width; }
        uint32 GetHeight() const override { return m_Data.Height; }

        // Window attributes
        void SetEventCallback(const EventCallbackFn& callback) override { m_Data.EventCallback = callback; }
        void SetVSync(bool enabled) override;
        bool IsVSync() const override;

        virtual void* GetNativeWindow() const override { return m_Window; }

    private:
        virtual void Init(const WindowProps& props);
        virtual void Shutdown();

    private:
        GLFWwindow* m_Window;

        struct WindowData
        {
            std::string Title;
            uint32 Width, Height;
            bool VSync;

            EventCallbackFn EventCallback;
        };

        WindowData m_Data;
    };

}