#include "window.h"
#include "glfwlibrary.h"
#include "utils.h"

namespace glfwW
{

void WindowCreationHints::resetToDefault()
{
    glfwDefaultWindowHints();
}

void WindowCreationHints::apply() const
{
    std::for_each(m_boolHints.cbegin(), m_boolHints.cend(), [this](const std::pair<WindowHint, bool>& hint){
        applyHint(hint.first, hint.second);
    });
    std::for_each(m_intHints.cbegin(), m_intHints.cend(), [this](const std::pair<WindowHint, int>& hint){
        applyHint(hint.first, hint.second);
    });
}

void WindowCreationHints::applyHint(WindowHint hint, bool value) const
{
    glfwWindowHint(glfwWindowHintValue(hint), value ? GLFW_TRUE :GLFW_FALSE);
}

void WindowCreationHints::applyHint(WindowHint hint, int value) const
{
    glfwWindowHint(glfwWindowHintValue(hint), value);
}

int glfwWindowHintValue(WindowHint hint)
{
    switch(hint)
    {
    case WindowHint::RESIZABLE:
        return GLFW_RESIZABLE;
    case WindowHint::VISIBLE:
        return GLFW_VISIBLE;
    case WindowHint::DECORATED:
        return GLFW_DECORATED;
    case WindowHint::FOCUSED:
        return GLFW_FOCUSED;
    case WindowHint::AUTO_ICONIFY:
        return GLFW_AUTO_ICONIFY;
    case WindowHint::FLOATING:
        return GLFW_FLOATING;
    case WindowHint::MAXIMIZED:
        return GLFW_MAXIMIZED;
    case WindowHint::CENTER_CURSOR:
        return GLFW_CENTER_CURSOR;
    case WindowHint::TRANSPARENT_FRAMEBUFFER:
        return GLFW_TRANSPARENT_FRAMEBUFFER;
    case WindowHint::FOCUS_ON_SHOW:
        return GLFW_FOCUS_ON_SHOW;
    case WindowHint::SCALE_TO_MONITOR:
        return GLFW_SCALE_TO_MONITOR;
    case WindowHint::SRGB_CAPABLE:
        return GLFW_SRGB_CAPABLE;
    case WindowHint::DOUBLE_BUFFER:
        return GLFW_DOUBLEBUFFER;
    case WindowHint::RED_BITS:
        return GLFW_RED_BITS;
    case WindowHint::GREEN_BITS:
        return GLFW_GREEN_BITS;
    case WindowHint::BLUE_BITS:
        return GLFW_BLUE_BITS;
    case WindowHint::ALPHA_BITS:
        return GLFW_ALPHA_BITS;
    case WindowHint::DEPTH_BITS:
        return GLFW_DEPTH_BITS;
    case WindowHint::STENCIL_BITS:
        return GLFW_STENCIL_BITS;
    case WindowHint::ACCUM_RED_BITS:
        return GLFW_ACCUM_RED_BITS;
    case WindowHint::ACCUM_GREEN_BITS:
        return GLFW_GREEN_BITS;
    case WindowHint::ACCUM_BLUE_BITS:
        return GLFW_BLUE_BITS;
    case WindowHint::ACCUM_ALPHA_BITS:
        return GLFW_ACCUM_ALPHA_BITS;
    case WindowHint::AUX_BUFFERS:
        return GLFW_AUX_BUFFERS;
    case WindowHint::SAMPLES:
        return GLFW_SAMPLES;
    case WindowHint::REFRESH_RATE:
        return GLFW_REFRESH_RATE;
    default:
        assert(false);
    }
    return -1;
}

std::unordered_map<GLFWwindow*, Window::CloseHandler> Window::closeHandlers;
std::unordered_map<GLFWwindow*, Window::SizeHandler> Window::sizeHandlers;
std::unordered_map<GLFWwindow*, Window::SizeHandler> Window::framebufferSizeHandlers;
std::unordered_map<GLFWwindow*, Window::SizeHandler> Window::positionHandlers;
std::unordered_map<GLFWwindow*, Window::RefreshHandler> Window::refreshHandlers;
std::unordered_map<GLFWwindow*, Window::ScaleHandler> Window::constentScaleHandlers;

void windowCloseCallback(GLFWwindow* window)
{
    Window(window, Window::WindowOwnership::None).onClose();
}

void windowSizeCallback(GLFWwindow* window, int width, int height)
{
    Window(window, Window::WindowOwnership::None).onSizeChanged(width, height);
}

void windowFramebufferSizeCallback(GLFWwindow* window, int width, int height)
{
    auto w = window;
    Window(window, Window::WindowOwnership::None).onFramebufferSizeChanged(width, height);
    assert(w == window);
}

void windowContentScaleCallback(GLFWwindow* window, float xscale, float yscale)
{
    Window(window, Window::WindowOwnership::None).onContentScaleChanged(xscale, yscale);
}

void windowPositionCallback(GLFWwindow* window, int x, int y)
{
    Window(window, Window::WindowOwnership::None).onPositionChanged(x, y);
}

void windowRefreshCallback(GLFWwindow* window)
{
    Window(window, Window::WindowOwnership::None).onRefresh();
}

Window::Window(GLFWwindow* window):
      m_window(window), m_ownership(WindowOwnership::None)
{
    assert(window);
}

Window::Window(Window&& rhs)
{
    std::swap(m_window, rhs.m_window);
    std::swap(m_ownership, rhs.m_ownership);
}

Window::~Window()
{
    if(m_window && m_ownership == WindowOwnership::Owner)
    {
        closeHandlers.erase(m_window);
        sizeHandlers.erase(m_window);
        framebufferSizeHandlers.erase(m_window);
        positionHandlers.erase(m_window);
        refreshHandlers.erase(m_window);

        glfwDestroyWindow(m_window);
    }
}

void Window::toggleFullscreen()
{
    if(!m_window)
    {
        return;
    }
    const auto monitor = getMonitor(*this);
    const auto mode = monitor.getVideoMode();
    setMonitor(monitor, {mode.width, mode.height}, mode.refreshRate);
}

}
