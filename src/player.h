#ifndef PLAYER_H
#define PLAYER_H

#include "camera.h"
#include "iListener.h"
#include "inputHandler.h"


class Player : public IKeyListener, public IMouseListener {
public:
    explicit Player(const glm::vec3 pos) : camera(pos,{0.0f, 1.0f, 0.0f}), playerPosition(pos) {}

    void tick(double dt);

    bool onKeyAction(GLFWwindow* window, int key, int scancode, int action, int mods) override;
    bool onMouseButtonAction(GLFWwindow* window, int button, int action, int mods) override;
    bool onMousePositionAction(GLFWwindow* window, double xPos, double yPos) override;

    glm::vec3 getPlayerPosition() const {return playerPosition;}

private:
    Camera camera;
    glm::vec3 playerPosition{0.0, 0.0, 0.0};
    double deltaTime{};
};



#endif //PLAYER_H
