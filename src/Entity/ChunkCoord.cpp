#include "ChunkCoord.hpp"
#include <SFML/System/Vector2.hpp>
#include <bits/c++config.h>
#include "../constants.hpp"


namespace entity {
    std::size_t coordHash::operator()(sf::Vector2i coord) const noexcept {
            std::size_t hx = std::hash<int>{}(coord.x);
            std::size_t hy = std::hash<int>{}(coord.y);
            return hx ^ (hy << 1);
        }
    sf::Vector2i getChunkCoord(sf::Vector2f position) {
        return sf::Vector2i(
            position.x * chunkRatio,
            position.y * chunkRatio
        );
    }
}
