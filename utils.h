#ifndef GLFWW_UTILS_H
#define GLFWW_UTILS_H

#include <vector>
#include "monitor.h"
#include "window.h"

namespace glfwW
{

template<typename T = decltype (GLFW_TRUE)>
T toGLFWBool(bool val)
{
    return val ? GLFW_TRUE : GLFW_FALSE;
}

std::vector<Monitor> getMonitors();
Monitor getMonitor(const Window& window);
WindowCreationHints currentWindowCreationHints();

}

#endif
