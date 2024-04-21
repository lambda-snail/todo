#pragma once

#include <cassert>
#include <GLFW/glfw3.h>

namespace LambdaSnail::Todo::UiHelpers {
    inline auto get_dpi_scale_factor() -> float {
        static float dpi_scale = -1.f;
        if (dpi_scale > 0.f) {
            return dpi_scale;
        }

        float _;
        glfwGetMonitorContentScale(glfwGetPrimaryMonitor(), &dpi_scale, &_);
        assert(dpi_scale > 0);
        return dpi_scale;
    }
}
