#pragma once
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <queue>
#include "Events.h"


class InputEventQueue
{
public:

    // Function to add an event to the queue
    void pushEvent(InputEvent& event) {
        eventQueue.push(event);
    }

    // Function to check if the event queue is empty
    bool hasEvents() {
        //return !eventQueue.empty();
        if (!eventQueue.empty()) {
            return true;
        }
        else {
            return false;
        }
    }

    // Function to get the next event from the queue
    InputEvent popEvent() {
        InputEvent event = eventQueue.front();
        eventQueue.pop();
        return event;
    }

private:
    std::queue<InputEvent> eventQueue;

};

