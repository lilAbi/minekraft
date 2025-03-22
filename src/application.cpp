

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
    renderer.init();


    //load resources

    //initialize world
    //generate initial terrain

    //initialize the player and camera
    inputHandler.addKeyListener(this, 100);
    inputHandler.addKeyListener(&player, 100);
    inputHandler.addMouseListener(&player, 100);

    //set app to running
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
    //Determine visible chunks via culling
    std::vector<glm::vec2> visibleChunks = world.getViewableChunks();

    //pass
    renderer.draw(player, window, std::move(visibleChunks));

    //renderer.draw(visibleChunks);


}

bool Application::onKeyAction(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
    return false;
}
