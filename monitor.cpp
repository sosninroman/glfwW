#include "monitor.h"

namespace glfwW
{

VideoMode Monitor::getVideoMode() const
{
    return m_monitor ? VideoMode(*glfwGetVideoMode(m_monitor)) : VideoMode();
}

std::vector<VideoMode> Monitor::getVideoModes() const
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

Vec2<int> Monitor::getPhysicalSize() const
{
    Vec2<int> result;
    if(m_monitor)
    {
        glfwGetMonitorPhysicalSize(m_monitor, &result.x, &result.y);
    }
    return result;
}

Vec2<float> Monitor::getContentScale() const
{
    Vec2<float> result;
    if(m_monitor)
    {
        glfwGetMonitorContentScale(m_monitor, &result.x, &result.y);
    }
    return result;
}

Vec2<int> Monitor::getPosition() const
{
    Vec2<int> result;
    if(m_monitor)
    {
        glfwGetMonitorPos(m_monitor, &result.x, &result.y);
    }
    return result;
}

Rect<int> Monitor::getWorkArea() const
{
    Rect<int> result;
    if(m_monitor)
    {
        glfwGetMonitorWorkarea(m_monitor, &result.position.x, &result.position.y, &result.size.x, &result.size.y);
    }
    return result;
}

std::string Monitor::getName() const
{
    return m_monitor ? std::string(glfwGetMonitorName(m_monitor)) : std::string();
}

void Monitor::setUserPointer(void* pointer)
{
    if(m_monitor)
    {
        glfwSetMonitorUserPointer(m_monitor, pointer);
    }
}

void* Monitor::getUserPointer() const
{
    return m_monitor ? glfwGetMonitorUserPointer(m_monitor) : nullptr;
}

}
