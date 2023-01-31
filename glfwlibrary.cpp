#include "glfwlibrary.h"
#include "utils.h"

namespace glfwW
{

void errorCallback(int errorCode, const char *description)
{
    GLFWlibrary::instance().onError(errorCode, description);
}

Error GLFWlibrary::init(InitHints hints)
{
    glfwInitHint(GLFW_JOYSTICK_HAT_BUTTONS, toGLFWBool(hints.joystickHatButtons));
    glfwInitHint(GLFW_COCOA_CHDIR_RESOURCES, toGLFWBool(hints.cocoaChdirResources));
    glfwInitHint(GLFW_COCOA_MENUBAR, toGLFWBool(hints.cocoaMenubar));

    glfwSetErrorCallback(errorCallback);

    if(glfwInit() != GLFW_TRUE)
    {
        return readLastError();
    }

    m_initialized = true;

    return Error();
}

Monitor GLFWlibrary::getPrimaryMonitor() const
{
    return Monitor(glfwGetPrimaryMonitor());
}

std::vector<Monitor> GLFWlibrary::getMonitors() const
{
    int count = 0;
    std::vector<Monitor> result;
    auto* glfwMonitors = glfwGetMonitors(&count);
    for(int i = 0; i < count; ++i)
    {
        result.push_back(Monitor(glfwMonitors[i]));
    }
    return result;
}

Window GLFWlibrary::createWindow(const Monitor& monitor, const std::string& title)
{
    const auto mode = monitor.getVideoMode();
    return createWindow(monitor, {mode.width, mode.height}, title);
}

Window GLFWlibrary::createWindow(const Monitor& monitor, Vec2<int> resolution, const std::string& title)
{
    return Window(glfwCreateWindow(resolution.x, resolution.y, title.data(), monitor.m_monitor, nullptr), Window::WindowOwnership::Owner);
}

Window GLFWlibrary::createWindow(Vec2<int> size, const std::string& title)
{
    return Window(glfwCreateWindow(size.x, size.y, title.data(), nullptr, nullptr), Window::WindowOwnership::Owner);
}

void GLFWlibrary::onError(int errorCode, const char *description) const
{
    if(m_errorHandler)
    {
        Error error;
        error.code = static_cast<ErrorCode>(errorCode);
        error.description.assign(description);
        std::invoke(*m_errorHandler, error);
    }
}

}
