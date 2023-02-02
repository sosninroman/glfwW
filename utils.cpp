#include "utils.h"

namespace glfwW
{

std::vector<Monitor> getMonitors()
{
    int count;
    GLFWmonitor** monitors = glfwGetMonitors(&count);

    std::vector<Monitor> result;
    result.reserve(count);
    for(int i = 0; i < count; ++i)
    {
        result.emplace_back(monitors[i]);
    }
    return result;
}

Monitor getMonitor(const Window& window)
{
    const auto monitors = getMonitors();

    const auto windowPos = window.getPosition();
    const auto windowSize = window.getSize();

    int bestOverlap = 0;
    Monitor result;

    for (const auto& monitor : monitors)
    {
        const auto mode = monitor.getVideoMode();
        const auto monitorPos = monitor.getPosition();
        const Vec2<int> monitorSize = {mode.width, mode.height};

        const auto overlap =
            std::max(0, std::min(windowPos.x + windowSize.x, monitorPos.x + monitorSize.x) - std::max(windowPos.x, monitorPos.x)) *
            std::max(0, std::min(windowPos.y + windowSize.y, monitorPos.y + monitorSize.y) - std::max(windowPos.y, monitorPos.y));

        if (bestOverlap < overlap) {
            bestOverlap = overlap;
            result = monitor;
        }
    }

    return result;
}

WindowCreationHints currentWindowCreationHints()
{
    WindowCreationHints hints;



    return hints;
}

}
