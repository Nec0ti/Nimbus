#pragma once

#include "Nimbus/Core/Base.h"
#include "Nimbus/Renderer/RenderCommand.h"
#include "Nimbus/Renderer/OrthographicCamera.h"
#include "Nimbus/Renderer/PerspectiveCamera.h"
#include "Nimbus/Renderer/Shader.h"
#include "Nimbus/Renderer/VertexArray.h"

namespace Nimbus {

    class NIMBUS_API Renderer
    {
    public:
        static void Init();
        static void Shutdown();
        
        static void OnWindowResize(uint32 width, uint32 height);

        static void BeginScene(OrthographicCamera& camera);
        static void BeginScene(PerspectiveCamera& camera);
        static void EndScene();

        static void Submit(const Ref<Shader>& shader, const Ref<VertexArray>& vertexArray, const glm::mat4& transform = glm::mat4(1.0f));

        static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
    private:
        struct SceneData
        {
            glm::mat4 ViewProjectionMatrix;
        };

        static Scope<SceneData> s_SceneData;
    };

}