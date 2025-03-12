#ifndef IKEYLISTENER_H
#define IKEYLISTENER_H

#include "GLFW/glfw3.h"

class IKeyListener {
public:
  virtual ~IKeyListener() = default;
  virtual bool onKeyAction(GLFWwindow* window, int key, int scancode, int action, int mods) = 0;
};

class IMouseListener {
public:
  virtual ~IMouseListener() = default;
  virtual bool onMouseButtonAction(GLFWwindow* window, int button, int action, int mods) = 0;
  virtual bool onMousePositionAction(GLFWwindow* window, double xPos, double yPos) = 0;
};


#endif //IKEYLISTENER_H
