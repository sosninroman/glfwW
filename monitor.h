#ifndef MONITOR_H
#define MONITOR_H

#include <vector>
#include <string>
#include "GLFW/glfw3.h"

namespace glfwW
{

template<typename T>
struct Vec2
{
    T x = T();
    T y = T();
};

template<typename T>
struct Rect
{
    Vec2<T> position;
    Vec2<T> size;
};

/*!
 * \brief The video mode of a monitor
 */
struct VideoMode
{
    VideoMode() = default;
    explicit VideoMode(const GLFWvidmode& mode):
          width(mode.width),
          height(mode.height),
          redBits(mode.redBits),
          greenBits(mode.greenBits),
          blueBits(mode.blueBits),
          refreshRate(mode.refreshRate)
    {}

    /*!
     * \brief width (in screen coordinates)
     */
    int width = 0;
    /*!
     * \brief height (in screen coordinates)
     */
    int height = 0;
    /*!
     * \brief The bit depth of the red channel
     */
    int redBits = 0;
    /*!
     * \brief The bit depth of the green channel
     */
    int greenBits = 0;
    /*!
     * \brief The bit depth of the blue channel
     */
    int blueBits = 0;
    /*!
     * \brief The refresh rate (in Hz)
     */
    int refreshRate = 0;
};

/*!
 * \brief A monitor object represents a currently connected monitor
 */
class Monitor
{
    friend class GLFWlibrary;
    friend class Window;
private:
    Monitor(GLFWmonitor* descriptor):m_monitor(descriptor){}

public:
    Monitor() = default;

    VideoMode getVideoMode() const
    {
        return m_monitor ? VideoMode(*glfwGetVideoMode(m_monitor)) : VideoMode();
    }

    std::vector<VideoMode> getVideoModes() const
    {
        std::vector<VideoMode> result;
        int count = 0;

        if(m_monitor)
        {
            const GLFWvidmode* modes = glfwGetVideoModes(m_monitor, &count);
            for(int i = 0; i < count; ++i)
            {
                result.push_back(VideoMode(modes[i]));
            }
        }

        return result;
    }

    Vec2<int> getPhysicalSize() const
    {
        Vec2<int> result;
        if(m_monitor)
        {
            glfwGetMonitorPhysicalSize(m_monitor, &result.x, &result.y);
        }
        return result;
    }

    Vec2<float> getContentScale() const
    {
        Vec2<float> result;
        if(m_monitor)
        {
            glfwGetMonitorContentScale(m_monitor, &result.x, &result.y);
        }
        return result;
    }

    Vec2<int> position() const
    {
        Vec2<int> result;
        if(m_monitor)
        {
            glfwGetMonitorPos(m_monitor, &result.x, &result.y);
        }
        return result;
    }

    Rect<int> getWorkArea() const
    {
        Rect<int> result;
        if(m_monitor)
        {
            glfwGetMonitorWorkarea(m_monitor, &result.position.x, &result.position.y, &result.size.x, &result.size.y);
        }
        return result;
    }

    std::string getName() const
    {
        return m_monitor ? std::string(glfwGetMonitorName(m_monitor)) : std::string();
    }

    GLFWmonitor* getHandler() const {return m_monitor;}
private:
    GLFWmonitor* m_monitor = nullptr;
};

}

#endif
