#ifndef GLFWW_WINDOW_H
#define GLFWW_WINDOW_H

#include <cassert>
#include <unordered_map>
#include <algorithm>
#include <type_traits>
#include "monitor.h"
#include <functional>
#include <optional>

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
    CLIENT_API,
    CONTEXT_CREATION_API,
    CONTEXT_VERSION_MAJOR,
    CONTEXT_VERSION_MINOR,
    OPENGL_FORWARD_COMPAT,
    OPENGL_DEBUG_CONTEXT,
    OPENGL_PROFILE,
//    CONTEXT_ROBUSTNESS,
//    CONTEXT_RELEASE_BEHAVIOR,
//    CONTEXT_NO_ERROR
};

enum class ClientAPI
{
    NO_API,
    OPENGL,
    OPENGL_ES
};

enum class ContextCreationAPI
{
    NATIVE_CONTEXT_API,
    EGL_CONTEXT_API,
    OSMESA_CONTEXT_API
};

enum class OpenGLProfile
{
    OPENGL_ANY_PROFILE,
    OPENGL_COMPAT_PROFILE,
    OPENGL_CORE_PROFILE
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
    case WindowHint::OPENGL_FORWARD_COMPAT:
    case WindowHint::OPENGL_DEBUG_CONTEXT:
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
    case WindowHint::CONTEXT_VERSION_MAJOR:
    case WindowHint::CONTEXT_VERSION_MINOR:
    {
        return std::is_same_v<T, int>;
    }
    case WindowHint::CLIENT_API:
    {
        return std::is_same_v<T, ClientAPI>;
    }
    case WindowHint::CONTEXT_CREATION_API:
    {
        return std::is_same_v<T, ContextCreationAPI>;
    }
    case WindowHint::OPENGL_PROFILE:
    {
        return std::is_same_v<T, OpenGLProfile>;
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
        else if constexpr(std::is_same_v<T, ClientAPI>)
        {
            m_clientAPI = value;
        }
        else if constexpr(std::is_same_v<T, ClientAPI>)
        {
            m_contextCreationAPI = value;
        }
        else if constexpr(std::is_same_v<T, OpenGLProfile>)
        {
            m_openGlProfile = value;
        }
        return *this;
    }

    void clear();

private:
    friend class GLFWlibrary;

    static void resetToDefault();

    void apply() const;
    void applyHint(WindowHint hint, bool value) const;
    void applyHint(WindowHint hint, int value) const;
    void applyHint(ClientAPI value) const;
    void applyHint(ContextCreationAPI value) const;
    void applyHint(OpenGLProfile value) const;

    std::unordered_map<WindowHint, bool> m_boolHints;
    std::unordered_map<WindowHint, int> m_intHints;
    std::optional<ClientAPI> m_clientAPI;
    std::optional<ContextCreationAPI> m_contextCreationAPI;
    std::optional<OpenGLProfile> m_openGlProfile;
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
    Window(GLFWwindow* window);
    Window(const Window&) = delete;
    Window(Window&& rhs);
    ~Window();

    bool valid() const {return m_window;}

    //Callbacks
    /*!
     * \brief Sets a close event callback. The callback function is called directly after the close flag has been set.
     */
    void setCloseHandler(CloseHandler h);

    /*!
     * \brief Sets a size change callback. The callback function receives the new size, in screen coordinates, of the content area of the window when the window is resized.
     */
    void setSizeHandler(SizeHandler h);

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

    //Window closing
    /*!
     * \brief Returns true if the wrapper is valid and the window should be closed.
     */
    bool shouldClose() const;

    /*!
     * \brief Set close flag for the window.
     */
    void setShouldClose(bool val) const;

    //Window size
    /*!
     * \brief Sets window's size.
     * For full screen windows, the specified size becomes the new resolution of the window's desired video mode.
     * For windowed mode windows, this sets the size, in screen coordinates of the content area or content area of the window.
     */
    void setSize(Vec2<int> size) const;

    /*!
     * \brief Returns a size of the window. The window size is in screen coordinates!!!
     */
    Vec2<int> getSize() const;

    /*!
     * \brief Returns the distances, in screen coordinates, from the edges of the content area to the corresponding edges of the full window.
     */
    FrameSize getFrameSize() const;

    //-----------

    /*!
     * \brief Turns the window in a fullscreen mode.
     */
    void toggleFullscreen();

    /*!
     * \brief Sets monitor for the windowed  mode
     */
    void setMonitor(const Monitor& monitor, Vec2<int> size, int refreshRate) const
    {
        glfwSetWindowMonitor(m_window, monitor.getHandler(), 0, 0, size.x, size.y, refreshRate);
    }

    /*!
     * \brief Sets monitor for the windowed mode
     */
    void setMonitor(Vec2<int> position, Vec2<int> size) const
    {
        glfwSetWindowMonitor(m_window, nullptr, position.x, position.y, size.x, size.y, 0);
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

    void swapBuffers() const
    {
        if(m_window)
        {
            glfwSwapBuffers(m_window);
        }
    }

    /*!
     * \brief Returns the GLFW window handler
     */
    GLFWwindow* getHandler() const {return m_window;}

    bool ownHandler() const {return m_ownership == WindowOwnership::Owner;}

    //USER POINTER
    void setUserPointer(void* ptr) const;
    void* getUserPointer() const;

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
