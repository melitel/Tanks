#pragma once
#include <cstddef> 

enum class InputKey : std::size_t {
    W,
    A,
    S,
    D,
    Q,
    Space,
    Size // always keep this last to use as a count
};

constexpr std::size_t to_index(InputKey key) {
    return static_cast<std::size_t>(key);
}
