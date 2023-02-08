#ifndef GLFWW_WINDOW_H
#define GLFWW_WINDOW_H

#include <cassert>
#include <unordered_map>
#include <algorithm>
#include <type_traits>
#include "monitor.h"
#include <functional>
#include <optional>
#include <vector>

namespace glfwW
{

template<typename T = decltype (GLFW_TRUE)>
T toGLFWBool(bool val)
{
    return val ? GLFW_TRUE : GLFW_FALSE;
}

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
    CONTEXT_ROBUSTNESS,
    CONTEXT_RELEASE_BEHAVIOR,
    CONTEXT_NO_ERROR
};

enum class ClientAPI
{
    NO_API,
    OPENGL,
    OPENGL_ES
};

ClientAPI toClientAPI(int value);

enum class ContextCreationAPI
{
    NATIVE_CONTEXT_API,
    EGL_CONTEXT_API,
    OSMESA_CONTEXT_API
};

ContextCreationAPI toContextCreationAPI(int value);

enum class OpenGLProfile
{
    OPENGL_ANY_PROFILE,
    OPENGL_COMPAT_PROFILE,
    OPENGL_CORE_PROFILE
};

OpenGLProfile toOpenGLProfile(int value);

enum class ContextRobustness
{
    NO_ROBUSTNESS,
    NO_RESET_NOTIFICATION,
    LOSE_CONTEXT_ON_RESET
};

ContextRobustness toContextRobustness(int value);

enum class ContextReleaseBehavior
{
    ANY_RELEASE_BEHAVIOR,
    RELEASE_BEHAVIOR_FLUSH,
    RELEASE_BEHAVIOR_NONE
};

ContextReleaseBehavior toContextReleaseBehavior(int value);

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
    case WindowHint::CONTEXT_NO_ERROR:
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
    case WindowHint::CONTEXT_ROBUSTNESS:
    {
        return std::is_same_v<T, ContextRobustness>;
    }
    case WindowHint::CONTEXT_RELEASE_BEHAVIOR:
    {
        return std::is_same_v<T, ContextReleaseBehavior>;
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
        else if constexpr(std::is_same_v<T, ContextRobustness>)
        {
            m_contextRobustness = value;
        }
        else if constexpr(std::is_same_v<T, ContextReleaseBehavior>)
        {
            m_contextReleaseBehavior = value;
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
    void applyHint(ContextRobustness value) const;
    void applyHint(ContextReleaseBehavior value) const;

    std::unordered_map<WindowHint, bool> m_boolHints;
    std::unordered_map<WindowHint, int> m_intHints;
    std::optional<ClientAPI> m_clientAPI;
    std::optional<ContextCreationAPI> m_contextCreationAPI;
    std::optional<OpenGLProfile> m_openGlProfile;
    std::optional<ContextRobustness> m_contextRobustness;
    std::optional<ContextReleaseBehavior> m_contextReleaseBehavior;
};

void windowCloseCallback(GLFWwindow* window);
void windowSizeCallback(GLFWwindow* window, int width, int height);
void windowFramebufferSizeCallback(GLFWwindow* window, int width, int height);
void windowContentScaleCallback(GLFWwindow* window, float xscale, float yscale);
void windowPositionCallback(GLFWwindow* window, int x, int y);
void windowRefreshCallback(GLFWwindow* window);
void windowMinimizeCallback(GLFWwindow* window, int iconified);
void windowMaximizeCallback(GLFWwindow* window, int maximized);
void windowFocusCallback(GLFWwindow* window, int focused);

enum class WindowAttribute {
    // Window related attributes
    FOCUSED,
    ICONIFIED,
    MAXIMIZED,
    HOVERED,
    VISIBLE,
    RESIZABLE,
    DECORATED,
    AUTO_ICONIFY,
    FLOATING,
    TRANSPARENT_FRAMEBUFFER,
    FOCUS_ON_SHOW,
    // Context related attributes
    CLIENT_API,
    CONTEXT_CREATION_API,
    CONTEXT_VERSION_MAJOR,
    CONTEXT_VERSION_MINOR,
    CONTEXT_REVISION,
    OPENGL_FORWARD_COMPAT,
    OPENGL_DEBUG_CONTEXT,
    OPENGL_PROFILE,
    CONTEXT_RELEASE_BEHAVIOR,
    CONTEXT_NO_ERROR,
    CONTEXT_ROBUSTNESS,
};

template<typename T, WindowAttribute attribute>
constexpr bool isAppropriateWindowAttributeType()
{
    switch (attribute) {
    case WindowAttribute::FOCUSED:
    case WindowAttribute::ICONIFIED:
    case WindowAttribute::MAXIMIZED:
    case WindowAttribute::HOVERED:
    case WindowAttribute::VISIBLE:
    case WindowAttribute::RESIZABLE:
    case WindowAttribute::DECORATED:
    case WindowAttribute::AUTO_ICONIFY:
    case WindowAttribute::FLOATING:
    case WindowAttribute::TRANSPARENT_FRAMEBUFFER:
    case WindowAttribute::FOCUS_ON_SHOW:
    case WindowAttribute::OPENGL_FORWARD_COMPAT:
    case WindowAttribute::OPENGL_DEBUG_CONTEXT:
    case WindowAttribute::CONTEXT_NO_ERROR:
    {
        return std::is_same_v<T, bool>;
    }
    case WindowAttribute::CONTEXT_REVISION:
    case WindowAttribute::CONTEXT_VERSION_MAJOR:
    case WindowAttribute::CONTEXT_VERSION_MINOR:
    {
        return std::is_same_v<T, int>;
    }
    case WindowAttribute::CLIENT_API:
    {
        return std::is_same_v<T, ClientAPI>;
    }
    case WindowAttribute::CONTEXT_CREATION_API:
    {
        return std::is_same_v<T, ContextCreationAPI>;
    }
    case WindowAttribute::OPENGL_PROFILE:
    {
        return std::is_same_v<T, OpenGLProfile>;
    }
    case WindowAttribute::CONTEXT_RELEASE_BEHAVIOR:
    {
        return std::is_same_v<T, ContextReleaseBehavior>;
    }
    case WindowAttribute::CONTEXT_ROBUSTNESS:
    {
        return std::is_same_v<T, ContextRobustness>;
    }
    }
    return false;
}

class Window
{
    friend class GLFWlibrary;

    friend void windowCloseCallback(GLFWwindow* window);
    friend void windowSizeCallback(GLFWwindow* window, int width, int height);
    friend void windowFramebufferSizeCallback(GLFWwindow* window, int width, int height);
    friend void windowContentScaleCallback(GLFWwindow* window, float xscale, float yscale);
    friend void windowPositionCallback(GLFWwindow* window, int x, int y);
    friend void windowRefreshCallback(GLFWwindow* window);
    friend void windowMinimizeCallback(GLFWwindow* window, int iconified);
    friend void windowMaximizeCallback(GLFWwindow* window, int maximized);
    friend void windowFocusCallback(GLFWwindow* window, int focused);
public:
    typedef void(* CloseHandler) (const Window&);
    typedef void(* SizeHandler) (const Window&, Vec2<int>);
    typedef void(* ScaleHandler) (const Window&, Vec2<float>);
    typedef void(* PositionHandler) (const Window&, Vec2<int>);
    typedef void(* RefreshHandler) (const Window&);
    typedef void(* MinimizeHandler) (const Window&);
    typedef void(* MaximizeHandler) (const Window&);
    enum class RestoreMode
    {
        FromMinimized,
        FromMaximized
    };
    typedef void(* RestoreHandler) (const Window&, RestoreMode);
    typedef void(* FocusHandler) (const Window&, bool);

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

    // CALLBACKS
    /*!
     * \brief Sets a close event callback. The callback function is called directly after the close flag has been set.
     */
    void setCloseHandler(CloseHandler h) const;

    /*!
     * \brief Sets a size change callback. The callback function receives the new size, in screen coordinates, of the content area of the window when the window is resized.
     */
    void setSizeHandler(SizeHandler h) const;

    /*!
     * \brief Set a framebuffer size change callback. The callback function receives the new size of the framebuffer, in pixels.
     */
    void setFramebufferSizeCallback(SizeHandler h) const;

    /*!
     * \brief Set a window's content scale handler.
     */
    void setContentScaleHandler(ScaleHandler h) const;

    /*!
     * \brief Sets a window's position handler. The callback function receives the new position, in screen coordinates, of the upper-left corner of the content area when the window is moved.
     */
    void setPositionHandler(PositionHandler h) const;

    /*!
     * \brief Sets a minimization event handler.
     */
    void setMinimizeHandler(MinimizeHandler h) const;

    /*!
     * \brief Sets a maximization event handler.
     */
    void setMaximizeHandler(MaximizeHandler h) const;

    /*!
     * \brief Sets a restore event handler.
     */
    void setRestoreHandler(RestoreHandler h) const;

    /*!
     * \brief Sets a focus change callback. The callback function receives when the window gains or loses input focus, whether by the user, system or client code.
     */
    void setFocusHandler(FocusHandler h) const;

    /*!
     * \brief Sets the window's context refresh callback. The callback function is called when the contents of the window needs to be refreshed.
     */
    void setRefreshHandler(RefreshHandler h) const;

    //WINDOW CLOSING
    /*!
     * \brief Returns true if the wrapper is valid and the window should be closed.
     */
    bool shouldClose() const;

    /*!
     * \brief Set close flag for the window.
     */
    void setShouldClose(bool val) const;

    // WINDOW SIZE
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

    enum class SizeHint
    {
        Min,
        Max
    };

    /*!
     * \brief Sets window size limits.
     * ! If the window is full screen, the size limits only take effect once it is made windowed. If the window is not resizable, this function does nothing.
     */
    void setSizeLimits(int width, int height, SizeHint hint);

    /*!
     * \brief Sets window size limits.
     * ! If the window is full screen, the size limits only take effect once it is made windowed. If the window is not resizable, this function does nothing.
     */
    void setSizeLimits(int minWidth, int minHeight, int maxWidth, int maxHeight);

    /*!
     * \brief Changes aspect ration of the window.
     */
    void setAspectRatio(int numer, int denom);

    /*!
     * \brief Disable an aspect ratio setting for the window.
     */
    void disableAspectRatio();

    /*!
     * \brief Uses current window's size as an aspect ratio.
     */
    void setCurrentSizeAsAspectRatio();

    // FRAMEBUFFER SIZE
    /*!
     * \brief Return a size of the framebuffer of the window. Framebuffer size is measured in pixels.
     */
    Vec2<int> getFramebufferSize() const;

    // CONTENT SCALE
    /*!
     * \brief Returns the ratio between the current DPI and the platform's default DPI for the window.
     */
    Vec2<float> getContentScale() const;

    // WINDOW'S POSITION
    /*!
     * \brief Returns the window's upper-left corner in screen coordinate.
     */
    Vec2<int> getPosition() const;

    /*!
     * \brief Changes the window's upper-left corner in screen coordinate.
     */
    void setPosition(Vec2<int> position);

    // TITLE AND ICON
    /*!
     * \brief Set the window's title, encoded as UTF-8.
     */
    void setTitle(const char* str);

    /*!
     * \brief Sets icon.
     * ! If passed an array of candidate images, those of or closest to the sizes desired by the system are selected.
     */
    void setIcon(const std::vector<GLFWimage>& icons);

    // FULLSCREEN \ WINDOWED
    // !Full screen windows are associated with a specific monitor.
    /*!
     * \brief Returns true if the window is in fullscreen mode. Otherwise returns false.
     */
    bool isFullscreen() const;

    /*!
     * \brief Turns the window in a windowed mode.
     */
    void toggleWindowed(Vec2<int> position, Vec2<int> size) const;

    /*!
     * \brief Turns the window in a fullscreen mode into it's current monitor.
     */
    void toggleFullscreen();

    /*!
     * \brief Turns the window in a fullscreen mode into the specified monitor.
     */
    void toggleFullscreen(const Monitor& monitor, Vec2<int> size, int refreshRate) const;

    //MINIMAZE \ MAXIMAZE \ VISIBILITY

    /*!
     * \brief Minimizes the window.
     * ! When a full screen window is minimized, the original video mode of its monitor is restored until the user or application restores the window.
     */
    void minimize();

    /*!
     * \brief Returns true if the window can be minimized.
     */
    bool isMinimizeable() const;

    /*!
     * \brief Maximizes the window.
     * ! Fullscreen windows cannot be maximized and this function does nothing for a fullscreen window.
     */
    void maximize();

    /*!
     * \brief Returns true if the window can be maximized.
     */
    bool isMaximizeable() const;

    /*!
     * \brief Restores initial size of minimized (maximized) fullscrean window.
     * ! When a full screen window is restored, the desired video mode is restored to its monitor as well.
     */
    void restore();

    /*!
     * \brief Hides a windowed window. Does nothing if the window is fullscreen.
     */
    void hide();

    /*!
     * \brief Shows a hidden window.
     */
    void show();

    /*!
     * \brief Returns true if the window is visible.
     * \return
     */
    bool isVisible() const;

    // FOCUS \ ATTENTION
    /*!
     * \brief Gives an input focus to the window and bring it to the front.
     */
    void setFocus();

    /*!
     * \brief Returns true if the window is focused.
     */
    bool isFocused() const;

    /*!
     * \brief Notifies the user of an event inside the window.
     */
    void requestAttention();

    // TRANSPARENCY
    /*!
     * \brief Returns true if the framebuffer of the window is transparent.
     */
    bool isFramebufferTransparent() const;

    /*!
     * \brief Returns the opacity of the whole window (including any decorations).
     */
    float getOpacity() const;

    /*!
     * \brief Changes the opaciity of the whole window.
     */
    void setOpacity(float value);

    // ATTRIBUTES
    template<WindowAttribute attribute>
    auto getAttribute()
    {
        if constexpr(isAppropriateWindowAttributeType<bool, attribute>())
        {
            return m_window && glfwGetWindowAttrib(m_window, glfwWindowAttributeValue(attribute)) == GLFW_TRUE;
        }
        if constexpr(isAppropriateWindowAttributeType<int, attribute>())
        {
            return m_window ? glfwGetWindowAttrib(m_window, glfwWindowAttributeValue(attribute)) : 0;
        }
        if constexpr(isAppropriateWindowAttributeType<ClientAPI, attribute>())
        {
            return toClientAPI(glfwGetWindowAttrib(m_window, glfwWindowAttributeValue(attribute)));
        }
        if constexpr(isAppropriateWindowAttributeType<ContextCreationAPI, attribute>())
        {
            return toContextCreationAPI(glfwGetWindowAttrib(m_window, glfwWindowAttributeValue(attribute)));
        }
        if constexpr(isAppropriateWindowAttributeType<OpenGLProfile, attribute>())
        {
            return toOpenGLProfile(glfwGetWindowAttrib(m_window, glfwWindowAttributeValue(attribute)));
        }
        if constexpr(isAppropriateWindowAttributeType<ContextReleaseBehavior, attribute>())
        {
            return toContextReleaseBehavior(glfwGetWindowAttrib(m_window, glfwWindowAttributeValue(attribute)));
        }
        if constexpr(isAppropriateWindowAttributeType<ContextRobustness, attribute>())
        {
            return toContextRobustness(glfwGetWindowAttrib(m_window, glfwWindowAttributeValue(attribute)));
        }
    }

    /*!
     * \brief Changes GLFW_DECORATED attribute value for the window.
     */
    void setDecorated(bool val);

    /*!
     * \brief Changes GLFW_RESIZABLE attribute value for the window.
     */
    void setResizable(bool val);

    /*!
     * \brief Changes GLFW_FLOATING attribute value for the window.
     */
    void setFloating(bool val);

    /*!
     * \brief Changes GLFW_AUTO_ICONIFY attribute value for the window.
     */
    void setAutoMinimizable(bool val);

    /*!
     * \brief Changes GLFW_FOCUS_ON_SHOW attribute value for the window.
     */
    void setFocusOnShow(bool val);

    // USER POINTER
    void setUserPointer(void* ptr) const;
    void* getUserPointer() const;

    // HANDLER
    /*!
     * \brief Returns the GLFW window handler
     */
    GLFWwindow* getHandler() const {return m_window;}

    bool ownHandler() const {return m_ownership == WindowOwnership::Owner;}

    // BUFFER
    /*!
     * \brief Swaps the front and back buffers of the specified window.
     */
    void swapBuffers() const;

    // CONTEXT
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

    void onClose() const;
    void onSizeChanged(int width, int height) const;
    void onFramebufferSizeChanged(int width, int height) const;
    void onContentScaleChanged(float xscale, float yscale) const;
    void onPositionChanged(int x, int y) const;
    void onRefresh() const;
    void onMinimized() const;
    void onMaximized() const;
    void onRestored(RestoreMode mode) const;
    void onFocused(bool focused) const;
    int glfwWindowAttributeValue(WindowAttribute attribute);

    GLFWwindow* m_window = nullptr;

    static std::unordered_map<GLFWwindow*, CloseHandler> closeHandlers;
    static std::unordered_map<GLFWwindow*, SizeHandler> sizeHandlers;
    static std::unordered_map<GLFWwindow*, SizeHandler> framebufferSizeHandlers;
    static std::unordered_map<GLFWwindow*, PositionHandler> positionHandlers;
    static std::unordered_map<GLFWwindow*, RefreshHandler> refreshHandlers;
    static std::unordered_map<GLFWwindow*, ScaleHandler> constentScaleHandlers;
    static std::unordered_map<GLFWwindow*, MinimizeHandler> minimizeHandlers;
    static std::unordered_map<GLFWwindow*, MaximizeHandler> maximizeHandlers;
    static std::unordered_map<GLFWwindow*, RestoreHandler> restoreHandlers;
    static std::unordered_map<GLFWwindow*, FocusHandler> focusHandlers;

    WindowOwnership m_ownership = WindowOwnership::None;
};

}

#endif
