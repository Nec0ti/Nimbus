#pragma once

#include "gui/Panel.h"

namespace Nimbus {

    class GameView : public Panel {
    public:
        GameView();
        ~GameView() override = default;

        void Render() override;
    };

} // namespace Nimbus