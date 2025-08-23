#pragma once

#include "gui/Panel.h"

namespace Nimbus {

    class HierarchyPanel : public Panel {
    public:
        HierarchyPanel();
        ~HierarchyPanel() override = default;

        void Render() override;
    };

} // namespace Nimbus