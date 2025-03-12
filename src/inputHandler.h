#ifndef INPUTHANDLER_H
#define INPUTHANDLER_H

#include "eventManager.h"
#include "iListener.h"
#include "event.h"
#include <vector>
#include <memory>


struct MouseListenerEntry {
    IMouseListener* listener;
    int priority;  // Higher numbers mean higher priority.
};

struct KeyListenerEntry {
    IKeyListener* listener;
    int priority;  // Higher numbers mean higher priority.
};

class InputHandler {
public:
    bool init(EventManager& eventManager);

    void addMouseListener(IMouseListener* listener, int priority);
    void addKeyListener(IKeyListener* listener, int priority);

private:
    //events to listen for
    void onKeyEvent(std::shared_ptr<KeyEvent> event);
    void onMouseEvent(std::shared_ptr<MouseEvent> event);
    void onMousePositionEvent(std::shared_ptr<MousePosEvent> event);

private:
    std::vector<KeyListenerEntry> keyListeners;
    std::vector<MouseListenerEntry> mouseListeners;

};


//dispatch key presses to listeners


#endif //INPUTHANDLER_H
