#pragma once
#include <SFML/System/Vector2.hpp>

struct InputEvent {

    enum class Type {
        MouseClick,
        ButtonClick
    };

    Type type;
    int buttonType;
    bool buttonPressed;
    sf::Vector2i position;
};
