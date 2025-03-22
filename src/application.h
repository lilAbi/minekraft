#ifndef MINEKRAFT_APPLICATION_H
#define MINEKRAFT_APPLICATION_H

#include "window.h"
#include "eventManager.h"
#include "inputHandler.h"
#include "iListener.h"
#include "player.h"
#include "world.h"
#include "renderer.h"


class Application : public IKeyListener {
public:
    //initialize subsystems
    bool init();
    //run application loop
    void update();
    //cleanup resources
    void cleanUp();

private:
    //update game loop
    void tick(double deltaTime);
    //render current frame
    void render();

    bool onKeyAction(GLFWwindow *window, int key, int scancode, int action, int mods) override;

private:
    Window window;
    EventManager eventManager;
    InputHandler inputHandler;
    Player player{{0.0, 10.0, 0.0}};
    World world;
    Renderer renderer;
    //Player player;

    bool running = false;
    double deltaTime = 0.0f;

};


#endif //MINEKRAFT_APPLICATION_H
