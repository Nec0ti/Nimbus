#pragma once

#include "gui/Panel.h"

namespace Nimbus {

    class SceneView : public Panel {
    public:
        SceneView();
        ~SceneView() override = default;

        void Render() override;
    };

} // namespace Nimbus