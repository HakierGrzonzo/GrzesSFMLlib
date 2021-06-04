#pragma once

#include <SFML/System/Vector2.hpp>
#include <cmath>

// Some vector operations

/*
template <class T>
sf::Vector2f operator*(sf::Vector2f vector, T scalar) {
    return sf::Vector2f(vector.x * scalar, vector.y * scalar);
}
*/

template <class T> 
T maximize(T vec1, T vec2) {
    return T(abs(vec1.x) > abs(vec2.x) ? vec1.x : vec2.x,
            abs(vec1.y) > abs(vec2.y) ? vec1.y : vec2.y);
}

template <class T> 
T minimize(T vec1, T vec2) {
    return T(abs(vec1.x) < abs(vec2.x) ? vec1.x : vec2.x,
            abs(vec1.y) < abs(vec2.y) ? vec1.y : vec2.y);
}

template <class T> 
T length(sf::Vector2<T> vec) {
    return sqrt(sqr(vec.x) + sqr(vec.y));
}
#define explode(vec) vec.x, vec.y
#define explodeOp(vec, op) vec.x op, vec.y op

#define ensureSign(signNum, num) signNum * num < 0 ? -num : num

template <class T>
T ensureSignVec(T signVector, T mainVec) {
    return T(ensureSign(signVector.x, mainVec.x), ensureSign(signVector.y, mainVec.y));
}
