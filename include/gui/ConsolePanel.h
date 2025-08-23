#pragma once

#include "gui/Panel.h"

namespace Nimbus {

    class ConsolePanel : public Panel {
    public:
        ConsolePanel();
        ~ConsolePanel() override = default;

        void Render() override;
    };

} // namespace Nimbus