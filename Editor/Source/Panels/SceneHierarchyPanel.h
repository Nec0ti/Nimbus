#pragma once

#include "Nimbus/Core/Base.h"
#include "Nimbus/Scene/Scene.h"
#include "Nimbus/Scene/Entity.h"

namespace Nimbus {

    class SceneHierarchyPanel
    {
    public:
        SceneHierarchyPanel() = default;
        SceneHierarchyPanel(const Ref<Scene>& scene);

        void SetContext(const Ref<Scene>& scene);

        void OnImGuiRender();

        Entity GetSelectedEntity() const { return m_SelectionContext; }
        void SetSelectedEntity(Entity entity);

    private:
        void DrawEntityNode(Entity entity);
        void DrawComponents(Entity entity);

        template<typename T, typename UIFunction>
        static void DrawComponent(const std::string& name, Entity entity, UIFunction uiFunction);

    private:
        Ref<Scene> m_Context;
        Entity m_SelectionContext;
    };

}