#include "window.h"
#include "glfwlibrary.h"
#include "utils.h"

namespace glfwW
{

ClientAPI toClientAPI(int value)
{
    if(value == GLFW_NO_API)
    {
        return ClientAPI::NO_API;
    }
    else if(value == GLFW_OPENGL_API)
    {
        return ClientAPI::OPENGL;
    }
    else if(value == GLFW_OPENGL_ES_API)
    {
        return ClientAPI::OPENGL_ES;
    }
    return ClientAPI::NO_API;
}

ContextCreationAPI toContextCreationAPI(int value)
{
    if(value == GLFW_NATIVE_CONTEXT_API)
    {
        return ContextCreationAPI::NATIVE_CONTEXT_API;
    }
    else if(value == GLFW_EGL_CONTEXT_API)
    {
        return ContextCreationAPI::EGL_CONTEXT_API;
    }
    else if(value == GLFW_OSMESA_CONTEXT_API)
    {
        return ContextCreationAPI::OSMESA_CONTEXT_API;
    }
    return ContextCreationAPI::NATIVE_CONTEXT_API;
}

OpenGLProfile toOpenGLProfile(int value)
{
    if(value == GLFW_OPENGL_ANY_PROFILE)
    {
        return OpenGLProfile::OPENGL_ANY_PROFILE;
    }
    else if(value == GLFW_OPENGL_CORE_PROFILE)
    {
        return OpenGLProfile::OPENGL_CORE_PROFILE;
    }
    else if(value == GLFW_OPENGL_COMPAT_PROFILE)
    {
        return OpenGLProfile::OPENGL_COMPAT_PROFILE;
    }
    return OpenGLProfile::OPENGL_ANY_PROFILE;
}

ContextRobustness toContextRobustness(int value)
{
    if(value == GLFW_NO_ROBUSTNESS)
    {
        return ContextRobustness::NO_ROBUSTNESS;
    }
    else if(value == GLFW_NO_RESET_NOTIFICATION)
    {
        return ContextRobustness::NO_RESET_NOTIFICATION;
    }
    else if(value == GLFW_LOSE_CONTEXT_ON_RESET)
    {
        return ContextRobustness::LOSE_CONTEXT_ON_RESET;
    }
    return ContextRobustness::NO_ROBUSTNESS;
}

ContextReleaseBehavior toContextReleaseBehavior(int value)
{
    if(value == GLFW_ANY_RELEASE_BEHAVIOR)
    {
        return ContextReleaseBehavior::ANY_RELEASE_BEHAVIOR;
    }
    else if(value == GLFW_RELEASE_BEHAVIOR_FLUSH)
    {
        return ContextReleaseBehavior::RELEASE_BEHAVIOR_FLUSH;
    }
    else if(value == GLFW_RELEASE_BEHAVIOR_NONE)
    {
        return ContextReleaseBehavior::RELEASE_BEHAVIOR_NONE;
    }
    return ContextReleaseBehavior::ANY_RELEASE_BEHAVIOR;
}

void WindowCreationHints::clear()
{
    m_boolHints.clear();
    m_intHints.clear();
    m_clientAPI.reset();
    m_contextCreationAPI.reset();
}

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
    if(m_clientAPI)
    {
        applyHint(m_clientAPI.value());
    }
    if(m_contextCreationAPI)
    {
        applyHint(m_contextCreationAPI.value());
    }
    if(m_openGlProfile)
    {
        applyHint(m_openGlProfile.value());
    }
    if(m_contextRobustness)
    {
        applyHint(m_contextRobustness.value());
    }
    if(m_contextReleaseBehavior)
    {
        applyHint(m_contextReleaseBehavior.value());
    }
}

void WindowCreationHints::applyHint(WindowHint hint, bool value) const
{
    glfwWindowHint(glfwWindowHintValue(hint), value ? GLFW_TRUE :GLFW_FALSE);
}

void WindowCreationHints::applyHint(WindowHint hint, int value) const
{
    glfwWindowHint(glfwWindowHintValue(hint), value);
}

void WindowCreationHints::applyHint(ClientAPI value) const
{
    switch(value)
    {
    case ClientAPI::NO_API:
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        break;
    case ClientAPI::OPENGL:
        glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API);
        break;
    case ClientAPI::OPENGL_ES:
        glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
        break;
    }
}

void WindowCreationHints::applyHint(ContextCreationAPI value) const
{
    switch(value)
    {
    case ContextCreationAPI::EGL_CONTEXT_API:
    {
        glfwWindowHint(GLFW_CONTEXT_CREATION_API, GLFW_EGL_CONTEXT_API);
        break;
    }
    case ContextCreationAPI::NATIVE_CONTEXT_API:
    {
        glfwWindowHint(GLFW_CONTEXT_CREATION_API, GLFW_NATIVE_CONTEXT_API);
        break;
    }
    case ContextCreationAPI::OSMESA_CONTEXT_API:
    {
        glfwWindowHint(GLFW_CONTEXT_CREATION_API, GLFW_OSMESA_CONTEXT_API);
        break;
    }
    }
}

void WindowCreationHints::applyHint(OpenGLProfile value) const
{
    switch(value)
    {
    case OpenGLProfile::OPENGL_ANY_PROFILE:
    {
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_ANY_PROFILE);
        break;
    }
    case OpenGLProfile::OPENGL_COMPAT_PROFILE:
    {
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);
        break;
    }
    case OpenGLProfile::OPENGL_CORE_PROFILE:
    {
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        break;
    }
    }
}

void WindowCreationHints::applyHint(ContextRobustness value) const
{
    switch(value)
    {
    case ContextRobustness::NO_ROBUSTNESS:
    {
        glfwWindowHint(GLFW_CONTEXT_ROBUSTNESS, GLFW_NO_ROBUSTNESS);
        break;
    }
    case ContextRobustness::NO_RESET_NOTIFICATION:
    {
        glfwWindowHint(GLFW_CONTEXT_ROBUSTNESS, GLFW_NO_RESET_NOTIFICATION);
        break;
    }
    case ContextRobustness::LOSE_CONTEXT_ON_RESET:
    {
        glfwWindowHint(GLFW_CONTEXT_ROBUSTNESS, GLFW_LOSE_CONTEXT_ON_RESET);
        break;
    }
    }
}

void WindowCreationHints::applyHint(ContextReleaseBehavior value) const
{
    switch(value)
    {
    case ContextReleaseBehavior::ANY_RELEASE_BEHAVIOR:
    {
        glfwWindowHint(GLFW_CONTEXT_RELEASE_BEHAVIOR, GLFW_ANY_RELEASE_BEHAVIOR);
        break;
    }
    case ContextReleaseBehavior::RELEASE_BEHAVIOR_FLUSH:
    {
        glfwWindowHint(GLFW_CONTEXT_RELEASE_BEHAVIOR, GLFW_RELEASE_BEHAVIOR_FLUSH);
        break;
    }
    case ContextReleaseBehavior::RELEASE_BEHAVIOR_NONE:
    {
        glfwWindowHint(GLFW_CONTEXT_RELEASE_BEHAVIOR, GLFW_RELEASE_BEHAVIOR_NONE);
        break;
    }
    }
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
    case WindowHint::CLIENT_API:
        return GLFW_CLIENT_API;
    case WindowHint::CONTEXT_CREATION_API:
        return GLFW_CONTEXT_CREATION_API;
    case WindowHint::CONTEXT_VERSION_MAJOR:
        return GLFW_CONTEXT_VERSION_MAJOR;
    case WindowHint::CONTEXT_VERSION_MINOR:
        return GLFW_CONTEXT_VERSION_MINOR;
    case WindowHint::OPENGL_FORWARD_COMPAT:
        return GLFW_OPENGL_FORWARD_COMPAT;
    case WindowHint::OPENGL_DEBUG_CONTEXT:
        return GLFW_OPENGL_DEBUG_CONTEXT;
    case WindowHint::OPENGL_PROFILE:
        return GLFW_OPENGL_PROFILE;
    case WindowHint::CONTEXT_ROBUSTNESS:
        return GLFW_CONTEXT_ROBUSTNESS;
    case WindowHint::CONTEXT_RELEASE_BEHAVIOR:
        return GLFW_CONTEXT_RELEASE_BEHAVIOR;
    case WindowHint::CONTEXT_NO_ERROR:
        return GLFW_CONTEXT_NO_ERROR;
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
std::unordered_map<GLFWwindow*, Window::MinimizeHandler> Window::minimizeHandlers;
std::unordered_map<GLFWwindow*, Window::MaximizeHandler> Window::maximizeHandlers;
std::unordered_map<GLFWwindow*, Window::RestoreHandler> Window::restoreHandlers;
std::unordered_map<GLFWwindow*, Window::FocusHandler> Window::focusHandlers;
std::unordered_map<GLFWwindow*, Window::KeyHandler> Window::keyHandlers;

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

void windowMinimizeCallback(GLFWwindow* window, int iconified)
{
    if (iconified)
    {
        Window(window, Window::WindowOwnership::None).onMinimized();
    }
    else
    {
        Window(window, Window::WindowOwnership::None).onRestored(Window::RestoreMode::FromMinimized);
    }
}

void windowMaximizeCallback(GLFWwindow* window, int maximized)
{
    if (maximized)
    {
        Window(window, Window::WindowOwnership::None).onMaximized();
    }
    else
    {
        Window(window, Window::WindowOwnership::None).onRestored(Window::RestoreMode::FromMaximized);
    }
}

void windowFocusCallback(GLFWwindow* window, int focused)
{
    Window(window, Window::WindowOwnership::None).onFocused(focused);
}

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    KeyEvent event;
    event.key = fromGlfwKey(key);
    event.action = fromGlfwKeyAction(action);
    event.scancode = scancode;
    event.modifierBits = mods;
    Window(window, Window::WindowOwnership::None).onKeyEvent(event);
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

void Window::setCloseHandler(CloseHandler h) const
{
    assert(m_window);
    closeHandlers[m_window] = h;
    glfwSetWindowCloseCallback(m_window, windowCloseCallback);
}

void Window::setSizeHandler(SizeHandler h) const
{
    assert(m_window);
    sizeHandlers[m_window] = h;
    glfwSetWindowSizeCallback(m_window, windowSizeCallback);
}

void Window::setFramebufferSizeCallback(SizeHandler h) const
{
    assert(m_window);
    framebufferSizeHandlers[m_window] = h;
    glfwSetFramebufferSizeCallback(m_window, windowFramebufferSizeCallback);
}

void Window::setContentScaleHandler(ScaleHandler h) const
{
    assert(m_window);
    constentScaleHandlers[m_window] = h;
    glfwSetWindowContentScaleCallback(m_window, windowContentScaleCallback);
}

void Window::setPositionHandler(PositionHandler h) const
{
    assert(m_window);
    positionHandlers[m_window] = h;
    glfwSetWindowPosCallback(m_window, windowPositionCallback);
}

void Window::setMinimizeHandler(MinimizeHandler h) const
{
    assert(m_window);
    minimizeHandlers[m_window] = h;
    glfwSetWindowIconifyCallback(m_window, windowMinimizeCallback);
}

void Window::setMaximizeHandler(MaximizeHandler h) const
{
    assert(m_window);
    maximizeHandlers[m_window] = h;
    glfwSetWindowMaximizeCallback(m_window, windowMaximizeCallback);
}

void Window::setRestoreHandler(RestoreHandler h) const
{
    assert(m_window);
    restoreHandlers[m_window] = h;
    glfwSetWindowIconifyCallback(m_window, windowMinimizeCallback);
    glfwSetWindowMaximizeCallback(m_window, windowMaximizeCallback);
}

void Window::setFocusHandler(FocusHandler h) const
{
    assert(m_window);
    focusHandlers[m_window] = h;
    glfwSetWindowFocusCallback(m_window, windowFocusCallback);
}

void Window::setRefreshHandler(RefreshHandler h) const
{
    assert(m_window);
    refreshHandlers[m_window] = h;
    glfwSetWindowRefreshCallback(m_window, windowRefreshCallback);
}

void Window::setKeyHandler(KeyHandler h) const
{
    assert(m_window);
    keyHandlers[m_window] = h;
    glfwSetKeyCallback(m_window, keyCallback);
}

bool Window::shouldClose() const
{
    return m_window && glfwWindowShouldClose(m_window);
}

void Window::setShouldClose(bool val) const
{
    if(m_window)
    {
        glfwSetWindowShouldClose(m_window, val ? GLFW_TRUE : GLFW_FALSE);
    }
}

void Window::setSize(Vec2<int> size) const
{
    if(m_window)
    {
        glfwSetWindowSize(m_window, size.x, size.y);
    }
}

Vec2<int> Window::getSize() const
{
    Vec2<int> result;
    if(m_window)
    {
        glfwGetWindowSize(m_window, &result.x, &result.y);
    }
    return result;
}

FrameSize Window::getFrameSize() const
{
    FrameSize result;
    if(m_window)
    {
        glfwGetWindowFrameSize(m_window, &result.left, &result.top, &result.right, &result.bottom);
    }
    return result;
}

void Window::setSizeLimits(int width, int height, SizeHint hint)
{
    if(m_window)
    {
        switch(hint)
        {
        case SizeHint::Min:
            glfwSetWindowSizeLimits(m_window, width, height, GLFW_DONT_CARE, GLFW_DONT_CARE);
            break;
        case SizeHint::Max:
            glfwSetWindowSizeLimits(m_window, GLFW_DONT_CARE, GLFW_DONT_CARE, width, height);
            break;
        }
    }
}

void Window::setSizeLimits(int minWidth, int minHeight, int maxWidth, int maxHeight)
{
    if(m_window)
    {
        glfwSetWindowSizeLimits(m_window, minWidth, minHeight, maxWidth, maxHeight);
    }
}

void Window::setAspectRatio(int numer, int denom)
{
    if(m_window)
    {
        glfwSetWindowAspectRatio(m_window, numer, denom);
    }
}

void Window::disableAspectRatio()
{
    if(m_window)
    {
        glfwSetWindowAspectRatio(m_window, GLFW_DONT_CARE, GLFW_DONT_CARE);
    }
}

void Window::setCurrentSizeAsAspectRatio()
{
    if(m_window)
    {
        const auto size = getSize();
        setAspectRatio(size.x, size.y);
    }
}

Vec2<int> Window::getFramebufferSize() const
{
    Vec2<int> result;
    if(m_window)
    {
        glfwGetFramebufferSize(m_window, &result.x, &result.y);
    }
    return result;
}

Vec2<float> Window::getContentScale() const
{
    Vec2<float> result;
    if(m_window)
    {
        glfwGetWindowContentScale(m_window, &result.x, &result.y);
    }
    return result;
}

Vec2<int> Window::getPosition() const
{
    Vec2<int> result;
    if(m_window)
    {
        glfwGetWindowPos(m_window, &result.x, &result.y);
    }
    return result;
}

void Window::setPosition(Vec2<int> position)
{
    if(m_window)
    {
        glfwSetWindowPos(m_window, position.x, position.y);
    }
}

void Window::setTitle(const char* str)
{
    if(m_window && str)
    {
        glfwSetWindowTitle(m_window, str);
    }
}

void Window::setIcon(const std::vector<GLFWimage>& icons)
{
    if(m_window)
    {
        glfwSetWindowIcon(m_window, icons.size(), icons.data());
    }
}

bool Window::isFullscreen() const
{
    return  m_window && glfwGetWindowMonitor(m_window);
}

void Window::toggleWindowed(Vec2<int> position, Vec2<int> size) const
{
    glfwSetWindowMonitor(m_window, nullptr, position.x, position.y, size.x, size.y, 0);
}

void Window::toggleFullscreen()
{
    if(!m_window)
    {
        return;
    }
    const auto monitor = getContainingMonitor(*this);
    const auto mode = monitor.getVideoMode();
    toggleFullscreen(monitor, {mode.width, mode.height}, mode.refreshRate);
}

void Window::toggleFullscreen(const Monitor& monitor, Vec2<int> size, int refreshRate) const
{
    glfwSetWindowMonitor(m_window, monitor.getHandler(), 0, 0, size.x, size.y, refreshRate);
}

void Window::minimize()
{
    if(m_window)
    {
        glfwIconifyWindow(m_window);
    }
}

bool Window::isMinimizeable() const
{
    return m_window && glfwGetWindowAttrib(m_window, GLFW_ICONIFIED);
}

void Window::maximize()
{
    if(m_window)
    {
        glfwMaximizeWindow(m_window);
    }
}

bool Window::isMaximizeable() const
{
    return m_window && glfwGetWindowAttrib(m_window, GLFW_MAXIMIZED);
}

void Window::restore()
{
    if(m_window)
    {
        glfwRestoreWindow(m_window);
    }
}

void Window::hide()
{
    if(m_window)
    {
        glfwHideWindow(m_window);
    }
}

void Window::show()
{
    if(m_window)
    {
        glfwShowWindow(m_window);
    }
}

bool Window::isVisible() const
{
    return m_window && glfwGetWindowAttrib(m_window, GLFW_VISIBLE);
}

void Window::setFocus()
{
    if (m_window)
    {
        glfwFocusWindow(m_window);
    }
}

bool Window::isFocused() const
{
    return m_window && glfwGetWindowAttrib(m_window, GLFW_FOCUSED);
}

void Window::requestAttention()
{
    if(m_window)
    {
        glfwRequestWindowAttention(m_window);
    }
}

bool Window::isFramebufferTransparent() const
{
    return m_window && glfwGetWindowAttrib(m_window, GLFW_TRANSPARENT_FRAMEBUFFER);
}

float Window::getOpacity() const
{
    return m_window ? glfwGetWindowOpacity(m_window) : 0;
}

void Window::setOpacity(float value)
{
    if(m_window)
    {
        glfwSetWindowOpacity(m_window, value);
    }
}

void Window::setDecorated(bool val)
{
    if(m_window)
    {
        glfwSetWindowAttrib(m_window, GLFW_DECORATED, toGLFWBool(val));
    }
}

void Window::setResizable(bool val)
{
    if(m_window)
    {
        glfwSetWindowAttrib(m_window, GLFW_RESIZABLE, toGLFWBool(val));
    }
}

void Window::setFloating(bool val)
{
    if(m_window)
    {
        glfwSetWindowAttrib(m_window, GLFW_FLOATING, toGLFWBool(val));
    }
}

void Window::setAutoMinimizable(bool val)
{
    if(m_window)
    {
        glfwSetWindowAttrib(m_window, GLFW_AUTO_ICONIFY, toGLFWBool(val));
    }
}

void Window::setFocusOnShow(bool val)
{
    if(m_window)
    {
        glfwSetWindowAttrib(m_window, GLFW_FOCUS_ON_SHOW, toGLFWBool(val));
    }
}

void Window::setUserPointer(void* ptr) const
{
    if(!m_window)
    {
        return;
    }
    glfwSetWindowUserPointer(m_window, ptr);
}

void* Window::getUserPointer() const
{
    return glfwGetWindowUserPointer(m_window);
}

void Window::swapBuffers() const
{
    if(m_window)
    {
        glfwSwapBuffers(m_window);
    }
}

KeyAction Window::getKeyAction(Key key) const
{
    return fromGlfwKeyAction(glfwGetKey(m_window, toGlfwKey(key)));
}

bool Window::getStickyKeysMode() const
{
    return m_window ? glfwGetInputMode(m_window, GLFW_STICKY_KEYS) == GLFW_TRUE : false;
}

void Window::setStickyKeys(bool val)
{
    if(m_window)
    {
        glfwSetInputMode(m_window, GLFW_STICKY_KEYS, toGLFWBool(val));
    }
}

bool Window::getLockModifiersAvailable() const
{
    return m_window ? glfwGetInputMode(m_window, GLFW_LOCK_KEY_MODS) == GLFW_TRUE : false;
}

void Window::setLockModifiersAvailable(bool val)
{
    if(m_window)
    {
        glfwSetInputMode(m_window, GLFW_LOCK_KEY_MODS, toGLFWBool(val));
    }
}

void Window::onClose() const
{
    tryInvokeCallback(closeHandlers);
}

void Window::onSizeChanged(int width, int height) const
{
    tryInvokeCallback(sizeHandlers, Vec2<int>{width, height});
}

void Window::onFramebufferSizeChanged(int width, int height) const
{
    tryInvokeCallback(framebufferSizeHandlers, Vec2<int>{width, height});
}

void Window::onContentScaleChanged(float xscale, float yscale) const
{
    tryInvokeCallback(constentScaleHandlers, Vec2<float>{xscale, yscale});
}

void Window::onPositionChanged(int x, int y) const
{
    tryInvokeCallback(positionHandlers, Vec2<int>{x, y});
}

void Window::onRefresh() const
{
    tryInvokeCallback(refreshHandlers);
}

void Window::onMinimized() const
{
    tryInvokeCallback(minimizeHandlers);
}

void Window::onMaximized() const
{
    tryInvokeCallback(maximizeHandlers);
}

void Window::onRestored(RestoreMode mode) const
{
    tryInvokeCallback(restoreHandlers, mode);
}

void Window::onFocused(bool focused) const
{
    tryInvokeCallback(focusHandlers, focused);
}

void Window::onKeyEvent(KeyEvent event) const
{
    tryInvokeCallback(keyHandlers, event);
}

int Window::glfwWindowAttributeValue(WindowAttribute attribute)
{
    switch(attribute)
    {
    case WindowAttribute::RESIZABLE:
        return GLFW_RESIZABLE;
    case WindowAttribute::VISIBLE:
        return GLFW_VISIBLE;
    case WindowAttribute::DECORATED:
        return GLFW_DECORATED;
    case WindowAttribute::FOCUSED:
        return GLFW_FOCUSED;
    case WindowAttribute::AUTO_ICONIFY:
        return GLFW_AUTO_ICONIFY;
    case WindowAttribute::FLOATING:
        return GLFW_FLOATING;
    case WindowAttribute::MAXIMIZED:
        return GLFW_MAXIMIZED;
    case WindowAttribute::TRANSPARENT_FRAMEBUFFER:
        return GLFW_TRANSPARENT_FRAMEBUFFER;
    case WindowAttribute::FOCUS_ON_SHOW:
        return GLFW_FOCUS_ON_SHOW;
    case WindowAttribute::CLIENT_API:
        return GLFW_CLIENT_API;
    case WindowAttribute::CONTEXT_CREATION_API:
        return GLFW_CONTEXT_CREATION_API;
    case WindowAttribute::CONTEXT_VERSION_MAJOR:
        return GLFW_CONTEXT_VERSION_MAJOR;
    case WindowAttribute::CONTEXT_VERSION_MINOR:
        return GLFW_CONTEXT_VERSION_MINOR;
    case WindowAttribute::OPENGL_FORWARD_COMPAT:
        return GLFW_OPENGL_FORWARD_COMPAT;
    case WindowAttribute::OPENGL_DEBUG_CONTEXT:
        return GLFW_OPENGL_DEBUG_CONTEXT;
    case WindowAttribute::OPENGL_PROFILE:
        return GLFW_OPENGL_PROFILE;
    case WindowAttribute::CONTEXT_ROBUSTNESS:
        return GLFW_CONTEXT_ROBUSTNESS;
    case WindowAttribute::CONTEXT_RELEASE_BEHAVIOR:
        return GLFW_CONTEXT_RELEASE_BEHAVIOR;
    case WindowAttribute::CONTEXT_NO_ERROR:
        return GLFW_CONTEXT_NO_ERROR;
    default:
        assert(false);
    }
    return -1;
}

}
