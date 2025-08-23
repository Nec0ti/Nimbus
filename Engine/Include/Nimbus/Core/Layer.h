#pragma once

#include "Nimbus/Core/Base.h"
#include "Nimbus/Events/Event.h"
#include "Nimbus/Core/Timestep.h"

namespace Nimbus {

    class NIMBUS_API Layer
    {
    public:
        Layer(const std::string& name = "Layer");
        virtual ~Layer() = default;

        virtual void OnAttach() {}
        virtual void OnDetach() {}
        virtual void OnUpdate(Timestep ts) {}
        virtual void OnImGuiRender() {}
        virtual void OnEvent(Event& event) {}

        const std::string& GetName() const { return m_DebugName; }
    protected:
        std::string m_DebugName;
    };

}