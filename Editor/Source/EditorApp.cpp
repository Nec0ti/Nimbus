#include <Nimbus.h>
#include <Nimbus/Core/EntryPoint.h>

#include "EditorLayer.h"

namespace Nimbus {

    class NimbusEditorApp : public Application
    {
    public:
        NimbusEditorApp(const ApplicationCommandLineArgs& args)
            : Application(GetApplicationSpecification())
        {
            // TODO: Set based on args
            PushLayer(new EditorLayer());
        }

        ~NimbusEditorApp()
        {
        }

    private:
        ApplicationSpecification GetApplicationSpecification()
        {
            ApplicationSpecification spec;
            spec.Name = "Nimbus Engine Editor";
            spec.WindowWidth = 1920;
            spec.WindowHeight = 1080;
            spec.WindowMaximized = true;
            spec.EnableImGui = true;

            return spec;
        }
    };

    Application* CreateApplication(ApplicationCommandLineArgs args)
    {
        return new NimbusEditorApp(args);
    }

}