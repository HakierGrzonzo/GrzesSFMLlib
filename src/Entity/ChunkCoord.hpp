#pragma once
#include <SFML/System/Vector2.hpp>
#include <bits/c++config.h>
#include <functional>

namespace entity {
    
    struct coordHash {
        std::size_t operator()(sf::Vector2i coord) const noexcept;
    };
    sf::Vector2i getChunkCoord(sf::Vector2f position);
}
