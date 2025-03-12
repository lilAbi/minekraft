#ifndef MINEKRAFT_WINDOW_H
#define MINEKRAFT_WINDOW_H

#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "spdlog/spdlog.h"
#include "eventManager.h"

static void frameBufferSizeCallback(GLFWwindow* window, int width, int height);
static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
static void cursorPositionCallback(GLFWwindow* window, double xpos, double ypos);


class Window {
public:
    //initialize window
    bool init(EventManager* em);
public:
#ifdef __APPLE__
    int width{1920/2}, height{1080/2};
#else
    int width{1920}, height{1080};
#endif
    GLFWwindow* glfwWindowPtr{nullptr};
    EventManager* eventManager{nullptr};
};


#endif //MINEKRAFT_WINDOW_H
