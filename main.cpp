#include "glfwlibrary.h"
#include <iostream>
#include <filesystem>

void framebufferSizeCallback(const glfwW::Window&, glfwW::Vec2<int> size)
{
    glViewport(0, 0, size.x, size.y);
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(const glfwW::Window& window)
{
    if(glfwGetKey(window.getHandler(), GLFW_KEY_ESCAPE) == GLFW_PRESS)
        window.setShouldClose(true);
}

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

std::filesystem::path getPath(const char* dir, const char* file)
{
    return std::filesystem::path(dir) / std::filesystem::path(file);
}

int main()
{
    glfwW::GLFWlibrary &lib = glfwW::GLFWlibrary::instance();
    const auto error = lib.init();

    if (error.code != glfwW::ErrorCode::NO_ERROR) {
        std::cout << error.description;
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    glfwW::Window window = lib.createWindow({SCR_WIDTH, SCR_HEIGHT}, "glfwW demo");
    //glfwW::Window window = lib.createWindow(lib.getPrimaryMonitor(), "glfwW demo");
    if (!window.valid()) {
        return -1;
    }

    //const auto mode = lib.getPrimaryMonitor().getVideoMode();
    //window.setMonitor(lib.getPrimaryMonitor(), {mode.width, mode.height}, mode.refreshRate);

    //window.toggleFullscreen();

    if (!window.valid())
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        return -1;
    }
    window.activate();
    window.setFramebufferSizeCallback(framebufferSizeCallback);

    while (!window.shouldClose())
    {
        processInput(window);

        //render here
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        window.swapBuffers();
        lib.pollEvents();
    }

    return 0;
}
