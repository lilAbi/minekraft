#ifndef EVENT_H
#define EVENT_H

#include "GLFW/glfw3.h"
#include "spdlog/spdlog.h"


class Event {
protected:
    virtual ~Event() = default;
};

struct WindowResizeEvent final : public Event{
    int width, height;
};

struct KeyEvent final : public Event {
    KeyEvent(GLFWwindow* w, int k, int s, int a, int m)
        : window(w), key(k), scancode(s), action(a), mods(m){};
    GLFWwindow* window;
    int key, scancode, action, mods;
};

struct MouseEvent final : public  Event {
    MouseEvent(GLFWwindow* w, int b, int a, int m)
        : window(w), button(b), action(a), mods(m){};
    GLFWwindow* window;
    int button, action, mods;
};

struct MousePosEvent final : public Event {
    MousePosEvent(GLFWwindow* w, int x, int y)
        : window(w), xPos(x), yPos(y) {};
    GLFWwindow* window;
    double xPos, yPos;
};





#endif //EVENT_H
