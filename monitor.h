#ifndef GLFWW_MONITOR_H
#define GLFWW_MONITOR_H

#include <vector>
#include <string>
#include "defs.h"

namespace glfwW
{

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

public:
    Monitor(GLFWmonitor* descriptor = nullptr): m_monitor(descriptor){}

    /*!
     * \brief Returns current video mode.
     */
    VideoMode getVideoMode() const;

    /*!
     * \brief Returns available video modes for the monitor.
     */
    std::vector<VideoMode> getVideoModes() const;

    /*!
     * \brief Returns the physical size of a monitor in millimetres.
     * ! This has no relation to its current resolution, i.e. the width and height of its current video mode.
     */
    Vec2<int> getPhysicalSize() const;

    /*!
     * \brief The content scale is the ratio between the current DPI and the platform's default DPI.
     */
    Vec2<float> getContentScale() const;

    /*!
     * \brief Returns the position of the monitor on the virtual desktop (in screen coordinates).
     */
    Vec2<int> getPosition() const;

    /*!
     * \brief Returns the area of a monitorwhich is not occupied by global task bars or menu bars (in screen coordinates);
     */
    Rect<int> getWorkArea() const;

    /*!
     * \brief Returns a human-readable, UTF-8 encoded name of the monitor.
     */
    std::string getName() const;

    /*!
     * \brief Sets user pointer.
     */
    void setUserPointer(void* pointer);

    /*!
     * \brief Returns a pointer, assosiated with this monitor.
     */
    void* getUserPointer() const;

    GLFWmonitor* getHandler() const {return m_monitor;}

    bool isValid() const {return m_monitor;}

    //TODO gamma ramp
private:
    GLFWmonitor* m_monitor = nullptr;
};

}

#endif
