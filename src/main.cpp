#include <GL/glew.h>
#include <iostream>
#include <windows.h>
#include <GLFW/glfw3.h>

#include "renderer/renderer.h"
#include "parser/html.h"

int main();

int CALLBACK WinMain(
  __in  HINSTANCE hInstance,
  __in  HINSTANCE hPrevInstance,
  __in  LPSTR lpCmdLine,
  __in  int nCmdShow
) {
    main();
}

static int framerate = 30;

int main()
{
    if (!glfwInit())
    {
        std::cerr << "Error initing GLFW" << std::endl;
    }

    glfwSetErrorCallback([](int error, const char *description) {
        std::cerr << "Error: " << description << std::endl;
    });

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_COCOA_RETINA_FRAMEBUFFER, GLFW_TRUE);
    glfwWindowHint(GLFW_REFRESH_RATE, glfwGetVideoMode(glfwGetPrimaryMonitor())->refreshRate);
    GLFWwindow *window = glfwCreateWindow(1280, 720, "Zincon", nullptr, nullptr);
    if (!window)
    {
        std::cerr << "Error creating window" << std::endl;
    }
    glfwMakeContextCurrent(window);
    glfwSwapInterval(0);

    glfwSetWindowSizeCallback(window, [](GLFWwindow *window, int width, int height){
        glViewport(0, 0, width, height);
    });

    parser_html();

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(window);
        glfwPollEvents();
        render();
        Sleep(1000/framerate);
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}