#pragma once

#include "Nimbus/Core/Base.h"
#include "Nimbus/Core/Window.h"
#include "Nimbus/Events/Event.h"
#include "Nimbus/Events/ApplicationEvent.h"
#include "Nimbus/Core/LayerStack.h"
#include "Nimbus/Renderer/Renderer.h"
#include "Nimbus/ImGui/ImGuiLayer.h"

namespace Nimbus {

    struct ApplicationCommandLineArgs
    {
        int Count = 0;
        char** Args = nullptr;

        const char* operator[](int index) const
        {
            NIMBUS_CORE_ASSERT(index < Count, "Index out of range");
            return Args[index];
        }
    };

    struct ApplicationSpecification
    {
        std::string Name = "Nimbus Application";
        std::string WorkingDirectory;
        ApplicationCommandLineArgs CommandLineArgs;
        uint32 WindowWidth = 1600;
        uint32 WindowHeight = 900;
        bool WindowMaximized = false;
        bool EnableImGui = true;
    };

    class NIMBUS_API Application
    {
    public:
        Application(const ApplicationSpecification& specification);
        virtual ~Application();

        void Run();
        void Close();

        void OnEvent(Event& e);

        void PushLayer(Layer* layer);
        void PushOverlay(Layer* layer);

        Window& GetWindow() { return *m_Window; }
        
        static Application& Get() { return *s_Instance; }
        
        const ApplicationSpecification& GetSpecification() const { return m_Specification; }

    private:
        bool OnWindowClose(WindowCloseEvent& e);
        bool OnWindowResize(WindowResizeEvent& e);

    private:
        ApplicationSpecification m_Specification;
        Scope<Window> m_Window;
        ImGuiLayer* m_ImGuiLayer;
        bool m_Running = true;
        bool m_Minimized = false;
        LayerStack m_LayerStack;
        float m_LastFrameTime = 0.0f;

        static Application* s_Instance;
    };

    // To be defined in client
    Application* CreateApplication(ApplicationCommandLineArgs args);
}