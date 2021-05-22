#include "Utils-Position.hpp"
#include <cmath>
#include "constants.hpp"

// define a square macro
#define sqr(x) x*x

using namespace utils;

Position::Position() {
    xy = sf::Vector2f();
    rotation = 0;
}

Position::Position(float x, float y, float angle) {
    // ensure that angle is < 2π
    rotation = fmod(angle, 2 * pi);
    xy = sf::Vector2f(x, y);
}

Position::Position(sf::Vector2f vec, float angle) {
    xy = vec;
    rotation = angle;
}

float Position::distanceTo(const Position& other) {
    return sqrt(
        sqr(xy.x + other.xy.x) + sqr(xy.y + other.xy.y)
    );
}

void Position::pointTo(const Position& target) {
    sf::Vector2f positionDiffrance = target.xy - xy;
    rotation = atan(positionDiffrance.x / positionDiffrance.y);
}
