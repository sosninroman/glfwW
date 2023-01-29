#ifndef WINDOW_WR_H
#define WINDOW_WR_H

#include <GLFW/glfw3.h>
#include <cassert>
#include <unordered_map>
#include <algorithm>
#include <type_traits>
#include "monitor.h"
#include <functional>

namespace glfwW
{

enum class WindowHint
{
    //Window related hints
    RESIZABLE,
    VISIBLE,
    DECORATED,
    FOCUSED,
    AUTO_ICONIFY,
    FLOATING,
    MAXIMIZED,
    CENTER_CURSOR,
    TRANSPARENT_FRAMEBUFFER,
    FOCUS_ON_SHOW,
    SCALE_TO_MONITOR,
    //Framebuffer related hints
    RED_BITS,
    GREEN_BITS,
    BLUE_BITS,
    ALPHA_BITS,
    DEPTH_BITS,
    STENCIL_BITS,
    ACCUM_RED_BITS,
    ACCUM_GREEN_BITS,
    ACCUM_BLUE_BITS,
    ACCUM_ALPHA_BITS,
    AUX_BUFFERS,
    STEREO,
    SAMPLES,
    SRGB_CAPABLE,
    DOUBLE_BUFFER,
    //Monitor related hints
    REFRESH_RATE,
    //Context related hints
//    CLIENT_API,
//    CONTEXT_CREATION_API,
//    CONTEXT_VERSION_MAJOR,
//    CONTEXT_VERSION_MINOR,
//    OPENGL_FORWARD_COMPAT,
//    OPENGL_DEBUG_CONTEXT,
//    OPENGL_PROFILE,
//    CONTEXT_ROBUSTNESS,
//    CONTEXT_RELEASE_BEHAVIOR,
//    CONTEXT_NO_ERROR
};

template<typename T, WindowHint hint>
constexpr bool isAppropriateHintType()
{
    switch(hint)
    {
    case WindowHint::RESIZABLE:
    case WindowHint::VISIBLE:
    case WindowHint::DECORATED:
    case WindowHint::FOCUSED:
    case WindowHint::AUTO_ICONIFY:
    case WindowHint::FLOATING:
    case WindowHint::MAXIMIZED:
    case WindowHint::CENTER_CURSOR:
    case WindowHint::TRANSPARENT_FRAMEBUFFER:
    case WindowHint::FOCUS_ON_SHOW:
    case WindowHint::SCALE_TO_MONITOR:
    case WindowHint::SRGB_CAPABLE:
    case WindowHint::DOUBLE_BUFFER:
    {
        return std::is_same_v<T, bool>;
    }
    case WindowHint::RED_BITS:
    case WindowHint::GREEN_BITS:
    case WindowHint::BLUE_BITS:
    case WindowHint::ALPHA_BITS:
    case WindowHint::DEPTH_BITS:
    case WindowHint::STENCIL_BITS:
    case WindowHint::ACCUM_RED_BITS:
    case WindowHint::ACCUM_GREEN_BITS:
    case WindowHint::ACCUM_BLUE_BITS:
    case WindowHint::ACCUM_ALPHA_BITS:
    case WindowHint::AUX_BUFFERS:
    case WindowHint::SAMPLES:
    case WindowHint::REFRESH_RATE:
    {
        return std::is_same_v<T, int>;
    }
    }
    return false;
}

int glfwWindowHintValue(WindowHint hint);

struct FrameSize
{
    int left = 0;
    int top = 0;
    int right = 0;
    int bottom = 0;
};

class WindowCreationHints
{
public:

    template<WindowHint hint, typename T>
    WindowCreationHints& addHint(T value)
    {
        static_assert(isAppropriateHintType<T, hint>(), "Inappropriate type for window hint");
        if constexpr(std::is_same_v<T, bool>)
        {
            m_boolHints[hint] = value;
        }
        else if constexpr(std::is_same_v<T, int>)
        {
            m_intHints[hint] = value;
        }
        return *this;
    }

    void apply() const
    {
        std::for_each(m_boolHints.cbegin(), m_boolHints.cend(), [this](const std::pair<WindowHint, bool>& hint){
            applyHint(hint.first, hint.second);
        });
        std::for_each(m_intHints.cbegin(), m_intHints.cend(), [this](const std::pair<WindowHint, int>& hint){
            applyHint(hint.first, hint.second);
        });
    }
private:
    void applyHint(WindowHint hint, bool value) const
    {
        glfwWindowHint(glfwWindowHintValue(hint), value ? GLFW_TRUE :GLFW_FALSE);
    }

    void applyHint(WindowHint hint, int value) const
    {
        glfwWindowHint(glfwWindowHintValue(hint), value);
    }

    std::unordered_map<WindowHint, bool> m_boolHints;
    std::unordered_map<WindowHint, int> m_intHints;
};

void windowCloseCallback(GLFWwindow* window);
void windowSizeCallback(GLFWwindow* window, int width, int height);
void windowFramebufferSizeCallback(GLFWwindow* window, int width, int height);
void windowContentScaleCallback(GLFWwindow* window, float xscale, float yscale);
void windowPositionCallback(GLFWwindow* window, int x, int y);
void windowRefreshCallback(GLFWwindow* window);

class Window
{
    friend class GLFWlibrary;

    friend void windowCloseCallback(GLFWwindow* window);
    friend void windowSizeCallback(GLFWwindow* window, int width, int height);
    friend void windowFramebufferSizeCallback(GLFWwindow* window, int width, int height);
    friend void windowContentScaleCallback(GLFWwindow* window, float xscale, float yscale);
    friend void windowPositionCallback(GLFWwindow* window, int x, int y);
    friend void windowRefreshCallback(GLFWwindow* window);
public:
    typedef void(* CloseHandler) (const Window&);
    typedef void(* SizeHandler) (const Window&, Vec2<int>);
    typedef void(* ScaleHandler) (const Window&, Vec2<float>);
    typedef void(* PositionHandler) (const Window&, Vec2<int>);
    typedef void(* RefreshHandler) (const Window&);

    enum class WindowOwnership
    {
        None = 0,
        Owner
    };

private:
    Window(GLFWwindow* window, WindowOwnership ownership):
          m_window(window), m_ownership(ownership)
    {}
public:
    Window(GLFWwindow* window):
          m_window(window), m_ownership(WindowOwnership::None)
    {
        assert(window);
    }

    Window(const Window&) = delete;

    ~Window()
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

    bool valid() const {return m_window;}

    void setCloseHandler(CloseHandler h)
    {
        assert(m_window);
        closeHandlers[m_window] = h;
        glfwSetWindowCloseCallback(m_window, windowCloseCallback);
    }

    void setSizeHandler(SizeHandler h)
    {
        assert(m_window);
        sizeHandlers[m_window] = h;
        glfwSetWindowSizeCallback(m_window, windowSizeCallback);
    }

    void setFramebufferSizeCallback(SizeHandler h)
    {
        assert(m_window);
        framebufferSizeHandlers[m_window] = h;
        glfwSetFramebufferSizeCallback(m_window, windowFramebufferSizeCallback);
    }

    void setPositionHandler(PositionHandler h)
    {
        assert(m_window);
        positionHandlers[m_window] = h;
        glfwSetWindowPosCallback(m_window, windowPositionCallback);
    }

    void setRefreshHandler(RefreshHandler h)
    {
        assert(m_window);
        refreshHandlers[m_window] = h;
        glfwSetWindowRefreshCallback(m_window, windowRefreshCallback);
    }

    void setContentScaleHandler(ScaleHandler h) const
    {
        assert(m_window);
        constentScaleHandlers[m_window] = h;
        glfwSetWindowContentScaleCallback(m_window, windowContentScaleCallback);
    }


    /*!
     * \brief Make window's OpenGL context current
     */
    void activate() const
    {
        if(m_window)
        {
            glfwMakeContextCurrent(m_window);
        }
    }

    bool shouldClose() const
    {
        return m_window && glfwWindowShouldClose(m_window);
    }

    void setShouldClose(bool val) const
    {
        if(m_window)
        {
            glfwSetWindowShouldClose(m_window, val ? GLFW_TRUE : GLFW_FALSE);
        }
    }

    void swapBuffers() const
    {
        if(m_window)
        {
            glfwSwapBuffers(m_window);
        }
    }

    void setMonitor(const Monitor& monitor, Vec2<int> size, int refreshRate) const
    {
        glfwSetWindowMonitor(m_window, monitor.getHandler(), 0, 0, size.x, size.y, refreshRate);
    }

    void setMonitor(Vec2<int> position, Vec2<int> size) const
    {
        glfwSetWindowMonitor(m_window, nullptr, position.x, position.y, size.x, size.y, 0);
    }

    GLFWwindow* getHandler() const {return m_window;}

    Vec2<int> getSize() const
    {
        Vec2<int> result;
        if(m_window)
        {
            glfwGetWindowSize(m_window, &result.x, &result.y);
        }
        return result;
    }

    void setSize(Vec2<int> size) const
    {
        if(m_window)
        {
            glfwSetWindowSize(m_window, size.x, size.y);
        }
    }

    FrameSize getFrameSize() const
    {
        FrameSize result;
        if(m_window)
        {
            glfwGetWindowFrameSize(m_window, &result.left, &result.top, &result.right, &result.bottom);
        }
        return result;
    }

    Vec2<int> getFramebufferSize() const
    {
        Vec2<int> result;
        if(m_window)
        {
            glfwGetFramebufferSize(m_window, &result.x, &result.y);
        }
        return result;
    }

    void setSizeLimits(int minWidth, int minHeight, int maxWidth, int maxHeight)
    {
        if(m_window)
        {
            glfwSetWindowSizeLimits(m_window, minWidth, minHeight, maxWidth, maxHeight);
        }
    }

    void setAspectRatio(int numer, int denom)
    {
        if(m_window)
        {
            glfwSetWindowAspectRatio(m_window, numer, denom);
        }
    }

    Vec2<int> getPosition() const
    {
        Vec2<int> result;
        if(m_window)
        {
            glfwGetWindowPos(m_window, &result.x, &result.y);
        }
        return result;
    }

    void setPosition(Vec2<int> position) const
    {
        if(m_window)
        {
            glfwSetWindowPos(m_window, position.x, position.y);
        }
    }

    void hide() const
    {
        if(m_window)
        {
            glfwHideWindow(m_window);
        }
    }

    void show() const
    {
        if(m_window)
        {
            glfwShowWindow(m_window);
        }
    }

private:
    template<typename CallbacksContainerT, typename... Args>
    void tryInvokeCallback(const CallbacksContainerT& callbacksContainer, Args... args) const
    {
        auto itr = callbacksContainer.find(m_window);
        if (itr != callbacksContainer.end())
        {
            std::invoke(itr->second, *this, std::forward<Args>(args)...);
        }
    }

    void onClose() const
    {
        tryInvokeCallback(closeHandlers);
    }

    void onSizeChanged(int width, int height) const
    {
        tryInvokeCallback(sizeHandlers, Vec2<int>{width, height});
    }

    void onFramebufferSizeChanged(int width, int height) const
    {
        tryInvokeCallback(framebufferSizeHandlers, Vec2<int>{width, height});
    }

    void onContentScaleChanged(float xscale, float yscale) const
    {
        tryInvokeCallback(constentScaleHandlers, Vec2<float>{xscale, yscale});
    }

    void onPositionChanged(int x, int y) const
    {
        tryInvokeCallback(positionHandlers, Vec2<int>{x, y});
    }

    void onRefresh() const
    {
        tryInvokeCallback(refreshHandlers);
    }

    GLFWwindow* m_window = nullptr;

    static std::unordered_map<GLFWwindow*, CloseHandler> closeHandlers;
    static std::unordered_map<GLFWwindow*, SizeHandler> sizeHandlers;
    static std::unordered_map<GLFWwindow*, SizeHandler> framebufferSizeHandlers;
    static std::unordered_map<GLFWwindow*, PositionHandler> positionHandlers;
    static std::unordered_map<GLFWwindow*, RefreshHandler> refreshHandlers;
    static std::unordered_map<GLFWwindow*, ScaleHandler> constentScaleHandlers;

    WindowOwnership m_ownership = WindowOwnership::None;
};

}

#endif
