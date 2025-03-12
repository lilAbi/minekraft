

#include "application.h"

bool Application::init() {
    //initialize window
    if(const bool windowInit{window.init(&eventManager)}; !windowInit){
        return false;
    }

    //initialize inputhandler

    if(const bool handlerInit{inputHandler.init(eventManager)}; !handlerInit){
        return false;
    }

    //initialize renderer

    //load resources

    //initialize world
    //generate initial terrain

    //initialize the player and camera

    inputHandler.addKeyListener(this, 100);
    inputHandler.addKeyListener(&player, 100);
    inputHandler.addMouseListener(&player, 100);
    running = true;
    
    return true;
}

void Application::update() {
    double lastFrameTime = 0.0f;

    while(!glfwWindowShouldClose(window.glfwWindowPtr) && running){
        double currentFrameTime = glfwGetTime();
        deltaTime = currentFrameTime - lastFrameTime;
        lastFrameTime = currentFrameTime;

        glClearColor(0.5f, 0.2f, 0.7f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        tick(deltaTime);

        render();

        glfwSwapBuffers(window.glfwWindowPtr);
        glfwPollEvents();
    }

}

void Application::cleanUp() {


}

void Application::tick(const double deltaTime) {
    //update player movement
    player.tick(deltaTime);
    //update world
    world.tick(player.getPlayerPosition());
}

void Application::render() {

}

bool Application::onKeyAction(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
    return false;
}
