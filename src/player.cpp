

#include "player.h"

void Player::tick(double dt) {
    deltaTime = dt;
    spdlog::info("Player position: {} {} {}", playerPosition.x, playerPosition.y, playerPosition.z);
}

bool Player::onKeyAction(GLFWwindow* window, int key, int scancode, int action, int mods) {

    const float velocity = camera.movementSpeed * static_cast<float>(deltaTime);

    if (key == GLFW_KEY_W && (action == GLFW_REPEAT || action == GLFW_PRESS))
        playerPosition += camera.front * velocity;
    if (key == GLFW_KEY_S && (action == GLFW_REPEAT || action == GLFW_PRESS))
        playerPosition -= camera.front * velocity;
    if (key == GLFW_KEY_A && (action == GLFW_REPEAT || action == GLFW_PRESS))
        playerPosition -= camera.right * velocity;
    if (key == GLFW_KEY_D && (action == GLFW_REPEAT || action == GLFW_PRESS))
        playerPosition += camera.right * velocity;

    return false;
}

bool Player::onMouseButtonAction(GLFWwindow *window, int button, int action, int mods) {


    return false;
}

bool Player::onMousePositionAction(GLFWwindow *window, double xPos, double yPos) {

    const auto xPosIn = static_cast<float>(xPos);
    const auto yPosIn = static_cast<float>(yPos);

    if (camera.firstMouse) {
        camera.lastX = xPosIn;
        camera.lastY = yPosIn;
        camera.firstMouse = false;
    }
    const float xOffset = xPosIn - camera.lastX;
    const float yOffset = camera.lastY - yPosIn;

    camera.lastX = xPosIn;
    camera.lastY = yPosIn;

    camera.processMouseMovement(xOffset, yOffset);
    return false;
}

