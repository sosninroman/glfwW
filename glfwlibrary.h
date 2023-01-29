#ifndef GLFWLIBRARY_H
#define GLFWLIBRARY_H

//#include <GLFW/glfw3.h>
#include <cstring>
#include <functional>
#include <string>
#include "monitor.h"
#include "window_wr.h"

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
    NO_WINDOW_CONTEXT = 0x0001000A
};

struct Error
{
    ErrorCode code = ErrorCode::NO_ERROR;
    std::string description;
};

void errorCallback(int errorCode, const char *description);

class GLFWlibrary
{
public:
    typedef void(* ErrorHandler) (const Error&);


    struct InitHints
    {
        InitHints():
              joystickHatButtons(true),
              cocoaChdirResources(true),
              cocoaMenubar(true)
        {

        }
        bool joystickHatButtons;
        bool cocoaChdirResources;
        bool cocoaMenubar;
    };

    struct Version
    {
        int major;
        int minor;
        int revision;
        std::string versionString;
    };

public:

    static GLFWlibrary& instance()
    {
        static GLFWlibrary inst;
        return inst;
    }

private:
    GLFWlibrary() = default;
    ~GLFWlibrary()
    {
        deinit();
    }

public:
    Error init(InitHints hints = InitHints())
    {
        glfwInitHint(GLFW_JOYSTICK_HAT_BUTTONS, hints.joystickHatButtons ? GLFW_TRUE : GLFW_FALSE);
        glfwInitHint(GLFW_COCOA_CHDIR_RESOURCES, hints.cocoaChdirResources ? GLFW_TRUE : GLFW_FALSE);
        glfwInitHint(GLFW_COCOA_MENUBAR, hints.cocoaMenubar ? GLFW_TRUE : GLFW_FALSE);

        glfwSetErrorCallback(errorCallback);

        if(glfwInit() != GLFW_TRUE)
        {
            return readLastError();
        }

        m_initialized = true;

        return Error();
    }

    bool initialized() const {return m_initialized;}

    void deinit()
    {
        m_errorHandler = nullptr;
        glfwTerminate();
    }

    void setErrorCallback(ErrorHandler* handler)
    {
        m_errorHandler = handler;
    }

    Error readLastError() const
    {
        Error result;
        const char* err;
        result.code = static_cast<ErrorCode>(glfwGetError(&err));
        result.description.assign(err);
        return result;
    }

    Version version() const
    {
        Version result;
        glfwGetVersion(&result.major, &result.minor, &result.revision);
        const char* versionString = glfwGetVersionString();
        result.versionString.assign(versionString);
        return result;
    }

    Monitor getPrimaryMonitor() const
    {
        return Monitor(glfwGetPrimaryMonitor());
    }

    std::vector<Monitor> getMonitors() const
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

//    Window createWindow(Vec2<int> size, const std::string& title)
//    {
//        return Window(glfwCreateWindow(size.x, size.y, "title.data()", NULL, NULL));
//    }

    Window createWindow(Vec2<int> size, const std::string& title, const Monitor& monitor = Monitor())
    {
        return Window(glfwCreateWindow(size.x, size.y, title.data(), monitor.m_monitor, nullptr), Window::WindowOwnership::Owner);
    }

    Window createWindow(const WindowCreationHints& hints,  Vec2<int> size, const std::string& title, const Monitor& monitor = Monitor())
    {
        hints.apply();
        return createWindow(size, title, monitor);
    }

    void pollEvents() const
    {
        glfwPollEvents();
    }

private:
    friend void errorCallback(int errorCode, const char *description);

    void onError(int errorCode, const char *description) const
    {
        if(m_errorHandler)
        {
            Error error;
            error.code = static_cast<ErrorCode>(errorCode);
            error.description.assign(description);
            std::invoke(*m_errorHandler, error);
        }
    }

    bool m_initialized = false;
    ErrorHandler* m_errorHandler = nullptr;


};

}

#endif
