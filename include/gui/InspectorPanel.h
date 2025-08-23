#pragma once

#include "gui/Panel.h"

namespace Nimbus {

    class InspectorPanel : public Panel {
    public:
        InspectorPanel();
        ~InspectorPanel() override = default;

        void Render() override;
    };

} // namespace Nimbus