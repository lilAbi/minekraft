#ifndef CAMERA_H
#define CAMERA_H

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

class Camera {
public:
    Camera(glm::vec3 pos, glm::vec3 _up);

    glm::mat4 getViewMatrix(glm::vec3 position) const;

    void updateCameraVectors();

    void processMouseMovement(float xOffset, float yOffset);

    // camera Attributes
    //glm::vec3 position{0.0f, 0.0f, 0.0f};
    glm::vec3 front{0.0f, 0.0f, -1.0f};
    glm::vec3 up{0.0f, 1.0f, 0.0f};
    glm::vec3 right{};
    glm::vec3 worldUp{0.0f, 1.0f, 0.0f};
    // euler Angles
    float yaw{-90.0f};
    float pitch{0.0f};
    // camera options
    float movementSpeed{2.5f * 2};
    float mouseSensitivity{0.1f};
    float zoom{45.0f};

    bool firstMouse{true};

    float lastX{1920.0f/4}, lastY{1080.0f/4};
};



#endif //CAMERA_H
