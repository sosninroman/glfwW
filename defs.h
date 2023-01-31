#ifndef GLFWW_DEFS_H
#define GLFWW_DEFS_H

#include <GLFW/glfw3.h>

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

}

#endif
