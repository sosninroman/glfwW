#include "mouse.h"

namespace glfwW
{

int toGlfwCursorMode(CursorMode mode)
{
    int result = GLFW_CURSOR_NORMAL;

    switch(mode)
    {
    case CursorMode::NORMAL:
        result = GLFW_CURSOR_NORMAL;
        break;
    case CursorMode::HIDDEN:
        result = GLFW_CURSOR_HIDDEN;
        break;
    case CursorMode::DISABLED:
        result = GLFW_CURSOR_DISABLED;
        break;
    }
    return result;
}

CursorMode fromGlfwCursorMode(int mode)
{
    if(mode == GLFW_CURSOR_NORMAL)
    {
        return CursorMode::NORMAL;
    }
    else if(mode == GLFW_CURSOR_HIDDEN)
    {
        return CursorMode::HIDDEN;
    }
    else if(mode == GLFW_CURSOR_DISABLED)
    {
        return CursorMode::DISABLED;
    }
    return CursorMode::NORMAL;
}

}
