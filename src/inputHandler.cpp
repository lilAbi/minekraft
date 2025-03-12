

#include "inputHandler.h"

bool InputHandler::init(EventManager &eventManager) {

    eventManager.subscribe(this, &InputHandler::onKeyEvent);
    eventManager.subscribe(this, &InputHandler::onMouseEvent);
    eventManager.subscribe(this, &InputHandler::onMousePositionEvent);

    return true;
}

void InputHandler::addMouseListener(IMouseListener* listener, int priority) {
    mouseListeners.emplace_back(listener, priority);
    std::ranges::sort(mouseListeners,
        [](const MouseListenerEntry& a, const MouseListenerEntry& b) {
            return a.priority > b.priority;
    });
}

void InputHandler::addKeyListener(IKeyListener* listener, int priority) {
    keyListeners.emplace_back(listener, priority);
    std::ranges::sort(keyListeners,
        [](const KeyListenerEntry& a, const KeyListenerEntry& b) {
            return a.priority > b.priority;
    });
}

void InputHandler::onKeyEvent(std::shared_ptr<KeyEvent> event) {
    //iterate through the key listeners
    for (auto& [listener, priority] : keyListeners) {
        //break when the object request a break, normally in a ui or paused
        if(listener->onKeyAction(event->window, event->key, event->scancode, event->action, event->mods)){
            break;
        }
    }
}

void InputHandler::onMouseEvent(std::shared_ptr<MouseEvent> event) {
    //iterate through the key listeners
    for (auto& [listener, priority] : mouseListeners) {
        //break when the object request a break, normally in a ui or paused
        if(listener->onMouseButtonAction(event->window, event->button, event->action, event->mods)){
            break;
        }
    }
}

void InputHandler::onMousePositionEvent(std::shared_ptr<MousePosEvent> event) {
    //iterate through the key listeners
    for (auto& [listener, priority] : mouseListeners) {
        //break when the object request a break, normally in a ui or paused
        if(listener->onMousePositionAction(event->window, event->xPos, event->yPos)){
            break;
        }
    }
}


