#include "NimbusPCH.h"
#include "Nimbus/Core/Application.h"
#include "Nimbus/Core/Log.h"
#include "Nimbus/Renderer/Renderer.h"

#include <GLFW/glfw3.h>

namespace Nimbus {

    Application* Application::s_Instance = nullptr;

    Application::Application(const ApplicationSpecification& specification)
        : m_Specification(specification)
    {
        NIMBUS_CORE_ASSERT(!s_Instance, "Application already exists!");
        s_Instance = this;

        // Set working directory here
        if (!m_Specification.WorkingDirectory.empty())
        {
            std::filesystem::current_path(m_Specification.WorkingDirectory);
        }

        WindowProps windowProps(m_Specification.Name, 
                               m_Specification.WindowWidth, 
                               m_Specification.WindowHeight);
        m_Window = Window::Create(windowProps);
        m_Window->SetEventCallback(NIMBUS_BIND_EVENT_FN(Application::OnEvent));

        Renderer::Init();

        if (m_Specification.EnableImGui)
        {
            m_ImGuiLayer = new ImGuiLayer();
            PushOverlay(m_ImGuiLayer);
        }
    }

    Application::~Application()
    {
        Renderer::Shutdown();
    }

    void Application::PushLayer(Layer* layer)
    {
        m_LayerStack.PushLayer(layer);
        layer->OnAttach();
    }

    void Application::PushOverlay(Layer* layer)
    {
        m_LayerStack.PushOverlay(layer);
        layer->OnAttach();
    }

    void Application::Close()
    {
        m_Running = false;
    }

    void Application::OnEvent(Event& e)
    {
        EventDispatcher dispatcher(e);
        dispatcher.Dispatch<WindowCloseEvent>(NIMBUS_BIND_EVENT_FN(Application::OnWindowClose));
        dispatcher.Dispatch<WindowResizeEvent>(NIMBUS_BIND_EVENT_FN(Application::OnWindowResize));

        for (auto it = m_LayerStack.rbegin(); it != m_LayerStack.rend(); ++it)
        {
            if (e.Handled)
                break;
            (*it)->OnEvent(e);
        }
    }

    void Application::Run()
    {
        NIMBUS_CORE_INFO("Starting Nimbus Engine Application: {0}", m_Specification.Name);

        while (m_Running)
        {
            float time = (float)glfwGetTime();
            Timestep timestep = time - m_LastFrameTime;
            m_LastFrameTime = time;

            if (!m_Minimized)
            {
                // Update all layers
                for (Layer* layer : m_LayerStack)
                    layer->OnUpdate(timestep);

                // Render ImGui
                if (m_Specification.EnableImGui)
                {
                    m_ImGuiLayer->Begin();
                    for (Layer* layer : m_LayerStack)
                        layer->OnImGuiRender();
                    m_ImGuiLayer->End();
                }
            }

            m_Window->OnUpdate();
        }

        NIMBUS_CORE_INFO("Shutting down Nimbus Engine Application");
    }

    bool Application::OnWindowClose(WindowCloseEvent& e)
    {
        m_Running = false;
        return true;
    }

    bool Application::OnWindowResize(WindowResizeEvent& e)
    {
        if (e.GetWidth() == 0 || e.GetHeight() == 0)
        {
            m_Minimized = true;
            return false;
        }

        m_Minimized = false;
        Renderer::OnWindowResize(e.GetWidth(), e.GetHeight());

        return false;
    }

}