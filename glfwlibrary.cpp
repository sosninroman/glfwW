#include "glfwlibrary.h"

namespace glfwW
{

void errorCallback(int errorCode, const char *description)
{
    GLFWlibrary::instance().onError(errorCode, description);
}

}
