#include "../glfwlibrary.h"
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

    glfwW::WindowCreationHints hints;
    hints.addHint<glfwW::WindowHint::RESIZABLE>(false);

    glfwW::Window window = lib.createWindow(hints, {SCR_WIDTH, SCR_HEIGHT}, "glfwW demo");

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

    window.setKeyHandler([](const glfwW::Window& window, glfwW::KeyEvent event){
        std::cerr << event.scancode << "\n";
        if(event.action == glfwW::Action::PRESS && event.key == glfwW::Key::KEY_ESCAPE)
            {
            window.setShouldClose(true);
        }
    });

    window.setTextHandler([](const glfwW::Window&, unsigned int codepoint){
        std::cerr << (char)codepoint << "\n";
    });

    window.setMouseClickHandler([](const glfwW::Window&, glfwW::MouseButtonEvent event){
        if(event.action == glfwW::Action::PRESS)
            {
            switch(event.button)
            {
            case glfwW::MouseButton::LEFT_BUTTON:
                std::cerr << "pressed left mouse button" << "\n";
                break;
            case glfwW::MouseButton::RIGHT_BUTTON:
                std::cerr << "pressed right mouse button" << "\n";
                break;
            default:
                std::cerr << "pressed mouse button" << "\n";
            }
        }

    });

    window.activate();
    window.setFramebufferSizeCallback(framebufferSizeCallback);

    while (!window.shouldClose())
    {
        lib.pollEvents();
        //processInput(window);

        //render here
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        window.swapBuffers();
        lib.pollEvents();
    }

    return 0;
}
