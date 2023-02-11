#ifndef GLFWW_LIBRARY_H
#define GLFWW_LIBRARY_H

#include <cstring>
#include <functional>
#include <string>
#include "monitor.h"
#include "window.h"

namespace glfwW
{

enum class ErrorCode
{
    NO_ERROR = 0,
    NOT_INITIALIZED = 0x00010001,
    NO_CURRENT_CONTEXT = 0x00010002,
    INVALID_ENUM = 0x00010003,
    INVALID_VALUE = 0x00010004,
    OUT_OF_MEMORY = 0x00010005,
    API_UNAVAILABLE = 0x00010006,
    VERSION_UNAVAILABLE = 0x00010007,
    PLATFORM_ERROR = 0x00010008,
    FORMAT_UNAVAILABLE = 0x00010009,
    NO_WINDOW_CONTEXT = 0x0001000A,
};

struct Error
{
    ErrorCode code = ErrorCode::NO_ERROR;
    std::string description;
};

enum class MonitorEventType
{
    CONNECTED,
    DISCONNECTED
};

MonitorEventType fromGlfwMonitorEventType(int type);

struct MonitorEvent
{
    Monitor monitor;
    MonitorEventType type = MonitorEventType::CONNECTED;
};

void errorCallback(int errorCode, const char *description);
void monitorCallback(GLFWmonitor* monitor, int event);

/*!
 * \brief The GLFW library wrapper class
 */
class GLFWlibrary
{
public:
    typedef void(* ErrorHandler) (const Error&);
    typedef void(* MonitorHandler) (const MonitorEvent&);

    struct InitHints
    {
        InitHints():
              joystickHatButtons(true),
              cocoaChdirResources(true),
              cocoaMenubar(true)
        {

        }
        bool joystickHatButtons = true;
        bool cocoaChdirResources = true;
        bool cocoaMenubar = true;
    };

    struct Version
    {
        int major = 0;
        int minor = 0;
        int revision = 0;
        std::string versionString;
    };

public:

    static GLFWlibrary& instance()
    {
        static GLFWlibrary inst;
        return inst;
    }

    //INITIALIZATION
    /*!
     * \brief Initialize GLFW library. Has to be called before library using.
     */
    Error init(InitHints hints = InitHints());

    /*!
     * \brief Returns if GLFW has been initialized already.
     */
    bool initialized() const {return m_initialized;}

    void deinit()
    {
        m_errorHandler = nullptr;
        glfwTerminate();
    }

    //ERRORS
    void setErrorCallback(ErrorHandler* handler);

    Error readLastError() const
    {
        Error result;
        const char* err;
        result.code = static_cast<ErrorCode>(glfwGetError(&err));
        result.description.assign(err);
        return result;
    }

    //INFORMATION
    Version version() const
    {
        Version result;
        glfwGetVersion(&result.major, &result.minor, &result.revision);
        const char* versionString = glfwGetVersionString();
        result.versionString.assign(versionString);
        return result;
    }

    //MONITORS
    /*!
     * \brief Returns information about primary monitor
     */
    Monitor getPrimaryMonitor() const;

    /*!
     * \brief Returns information about all currently connected monitors
     * \return
     */
    std::vector<Monitor> getMonitors() const;

    /*!
     * \brief Returns current monitor for the window.
     */
    Monitor getContainingMonitor(const Window& window);

    /*!
     * \brief Sets monitor handler callback. Callback is invoked if monitor was connected or disconnected.
     */
    void setMonitorHandler(MonitorHandler* h);

    //WINDOWS
    /*!
     * \brief Creates a fullscreen window on a particular monitor
     */
    Window createWindow(const Monitor& monitor, const std::string& title);

    /*!
     * \brief Creates a fullscreen window on a particular monitor
     */
    Window createWindow(const Monitor& monitor, Vec2<int> resolution, const std::string& title);

    /*!
     * \brief Creates a new window in windowed mode
     */
    Window createWindow(Vec2<int> size, const std::string& title);

    /*!
     * \brief Creates a new window with particular creation hints
     */
    Window createWindow(const WindowCreationHints& hints,  Vec2<int> size, const std::string& title);

    /*!
     * \brief Returns a set of window creation hints which were changed by this wrapper.
     */
    WindowCreationHints getWindowCreationHints() const;

    /*!
     * \brief Changes given window creation hints.
     */
    void apply(WindowCreationHints hints);

    /*!
     * \brief Resets window creation hints to default values.
     */
    void resetWindowCreationHintsToDefault();

    //EVENTS
    /*!
     * \brief Processes events from the event queue immediately. Processing events will cause the window and input callbacks associated with those events to be called.
     */
    void pollEvents() const;

    /*!
     * \brief Puts the calling thread to sleep until at least one event is available in the event queue.
     * Once one or more events are available, the events in the queue are processed and the function then returns immediately.
     */
    void waitEvents() const;

    /*!
     * \brief Puts the calling thread to sleep until at least one event is available in the event queue, or until the specified timeout is reached.
     */
    void waitEventsTimeout(double time) const;

    // KEYBOARD
    /*!
     * \brief Returns scancode for the key
     */
    int getKeyScancode(Key key) const;

    const char* getKeyName(Key key) const;
    const char* getKeyName(int scancode);

    // MOUSE
    bool isRawMouseMotionSupported() const;
private:
    friend void errorCallback(int errorCode, const char *description);
    friend void monitorCallback(GLFWmonitor* monitor, int event);

    GLFWlibrary() = default;

    ~GLFWlibrary()
    {
        deinit();
    }

    void onError(int errorCode, const char *description) const;
    void onMonitorEvent(GLFWmonitor* monitor, int event) const;

private:
    bool m_initialized = false;
    ErrorHandler* m_errorHandler = nullptr;
    MonitorHandler* m_monitorHandler = nullptr;
    WindowCreationHints m_currentHints;
};

}

#endif
