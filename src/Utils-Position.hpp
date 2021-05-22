#pragma once
#include <SFML/System/Vector2.hpp>

namespace utils {
    class Position {
    public:
        sf::Vector2f xy;
        float rotation; // in radians
        Position();
        Position(float x, float y, float angle = 0);
        Position(sf::Vector2f vec, float angle = 0);
        float distanceTo(const Position& other);
        void pointTo(const Position& target);
    protected:
    };
};
