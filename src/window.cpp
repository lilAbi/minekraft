#include "window.h"

#include "event.h"

bool Window::init(EventManager* em) {

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
#ifdef __APPLE__
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // Required on Mac
    glfwWindowHint(GLFW_COCOA_RETINA_FRAMEBUFFER, GLFW_TRUE);
#else
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
#endif
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    glfwWindowPtr = glfwCreateWindow(width, height, "minekraft", nullptr, nullptr);

    //test window creation
    if(!glfwWindowPtr){
        spdlog::info("Failed to create window");
        glfwTerminate();
        return false;
    }

    glfwMakeContextCurrent(glfwWindowPtr);
    glfwSetWindowUserPointer(glfwWindowPtr, static_cast<void*>(this));
    glfwSetFramebufferSizeCallback(glfwWindowPtr, frameBufferSizeCallback);
    glfwSetKeyCallback(glfwWindowPtr, keyCallback);
    glfwSetCursorPosCallback(glfwWindowPtr, cursorPositionCallback);

    //glfwSetInputMode(glfwWindowPtr, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        spdlog::info("Failed to initialize GLAD");
        return false;
    }

    eventManager = em;
    return true;
}

static void frameBufferSizeCallback(GLFWwindow* window, int width, int height){
    if(auto* handle{static_cast<Window*>(glfwGetWindowUserPointer(window))}; handle){
        handle->width = width;
        handle->height = height;
        glViewport(0, 0, width, height);
    }
}

static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if(const auto* handle{static_cast<Window*>(glfwGetWindowUserPointer(window))}; handle) {
        handle->eventManager->publish( std::make_shared<KeyEvent>(window, key, scancode, action, mods) );
    }
}

static void cursorPositionCallback(GLFWwindow* window, double xpos, double ypos) {
    if(const auto* handle{static_cast<Window*>(glfwGetWindowUserPointer(window))}; handle) {
        handle->eventManager->publish( std::make_shared<MousePosEvent>(window, xpos, ypos) );
    }
}
