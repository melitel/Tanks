#pragma once
#include "InputKeys.h"
#include <SFML/System/Vector2.hpp>

struct InputEvent {

    enum class Type {
        MouseClick,
        ButtonClick
    };

    Type type;
    InputKey key_pressed;
    bool buttonPressed;
    sf::Vector2i position;
};
