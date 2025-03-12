#ifndef EVENTHANDLER_H
#define EVENTHANDLER_H

#include <spdlog/spdlog.h>
#include <functional>
#include <memory>

class Event;

//handle different types of events for different classes
class BaseEventFuncHandler{
public:
    virtual ~BaseEventFuncHandler() = default;
    virtual void call(std::shared_ptr<Event> event) = 0;
};

template<typename T, typename EventType>
class MemberFuncEventHandler : public BaseEventFuncHandler {
    using OnEventMemberFunc = void(T::*)(std::shared_ptr<EventType>);
public:
    MemberFuncEventHandler(T* i, const OnEventMemberFunc func) : instance(i), onEventMemberFunc(func) {};

    void call(std::shared_ptr<Event> event) override {
        (instance->*onEventMemberFunc)(std::static_pointer_cast<EventType>(event));
    }

private:
    T* instance;
    OnEventMemberFunc onEventMemberFunc;
};


#endif //EVENTHANDLER_H
