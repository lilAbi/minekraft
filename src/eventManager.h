#ifndef EVENTMANAGER_H
#define EVENTMANAGER_H

#include "absl/container/flat_hash_map.h"
#include <typeindex>
#include <vector>
#include <memory>
#include "eventHandler.h"
#include "spdlog/spdlog.h"



//Event manager
class EventManager{
    using EventHandlerVec = std::vector<std::shared_ptr<BaseEventFuncHandler>>;
public:
    EventManager(){
        spdlog::info("Initializing Event Manager");
    };

    template<typename EventType>
    void publish(std::shared_ptr<EventType> event);

    template<typename T, typename EventType>
    void subscribe(T* instance, void (T::*OnEventMemberFunc)(std::shared_ptr<EventType> event));
private:
    //each index in the map holds a vector of related eventHandlers that do different things
    //std::map<std::type_index, std::shared_ptr<EventHandlerVec>> subscribers;
    absl::flat_hash_map<std::type_index, std::shared_ptr<EventHandlerVec>> subscribers;
};

//void EventManager::publish(EventType* eventType)
template<typename EventType>
void EventManager::publish(std::shared_ptr<EventType> event) {
    //grab the incoming EventType's Vectors of EventHandlers
    if(std::shared_ptr<EventHandlerVec> currEventTypeVec{subscribers[typeid(EventType)]}; currEventTypeVec){
        //loop through the EventTypeVec and fire the event for different systems subscribed for a particular event type
        for(auto& eventHandler:  *currEventTypeVec){
            if(eventHandler){
                eventHandler->call(std::static_pointer_cast<Event>(event));
            }
        }
    }
}

template<typename T, typename EventType>
void EventManager::subscribe(T* instance, void (T::*OnEventMemberFunc)(std::shared_ptr<EventType> event)) {
    //if the key is not found, add it
    const std::type_index id{typeid(EventType)};
    if(subscribers.find(id) == subscribers.end()){
        subscribers[id] = std::make_shared<EventHandlerVec>();
    }
    subscribers[id]->push_back(std::make_shared< MemberFuncEventHandler<T,EventType>>(instance, OnEventMemberFunc));
}


#endif //EVENTMANAGER_H
