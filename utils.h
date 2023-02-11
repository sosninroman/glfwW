#ifndef GLFWW_UTILS_H
#define GLFWW_UTILS_H

#include <vector>
#include "monitor.h"
#include "window.h"

namespace glfwW
{

bool fromGLFWBool(int val);
std::vector<Monitor> getMonitors();
Monitor getContainingMonitor(const Window& window);

}

#endif
