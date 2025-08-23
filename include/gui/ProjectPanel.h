#pragma once

#include "gui/Panel.h"

namespace Nimbus {

    class ProjectPanel : public Panel {
    public:
        ProjectPanel();
        ~ProjectPanel() override = default;

        void Render() override;
    };

} // namespace Nimbus