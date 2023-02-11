#ifndef GLFWW_MOUSE_H
#define GLFWW_MOUSE_H

#include "defs.h"

namespace glfwW
{

enum class CursorMode
{
    NORMAL,
    HIDDEN,
    DISABLED
};

int toGlfwCursorMode(CursorMode mode);
CursorMode fromGlfwCursorMode(int mode);

}

#endif
