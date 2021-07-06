#pragma once

#include <stdexcept>
#include <iostream>
#include "constants.hpp"
#define add_component(name) components.push_back(std::unique_ptr<component::Component>( \
            dynamic_cast<component::Component*>( \
              new name( \
                  dynamic_cast<entity::Entity*>(this))))); 

//#define debug

#ifdef debug
#define print(var) std::cerr << "\33[2K" << __FILE__ << ":" << __LINE__ << "\t" << #var << " -> \t" << var << std::endl;
#define printVec2(var) std::cerr << "\33[2K" << __FILE__ << ":" << __LINE__ << "\t" << #var << " -> \t(" << var.x << "; " << var.y << ")" << std::endl;
#undef debug
#else
#define print(x) ;
#define printVec2(x) ;
#endif

#define assertCond(condition, msg) if(condition) { \
    std::cerr << "ASSERTION: " << __FILE__ << ":" << __LINE__ << "\t->\t" << #condition << std::endl; \
    throw std::runtime_error(msg); \
}

#define assertNotNull(ptr) if(ptr == nullptr) { \
    std::cerr << "ASSERTION: " << __FILE__ << ":" << __LINE__ << "\t->\t" << #ptr << " is null" << std::endl; \
    throw std::runtime_error("Failed Assertion check"); \
}

#define elif else if

// vector conversions
#define sf2box(vec) b2Vec2(vec.x / box2sfRatio, vec.y / box2sfRatio)
#define box2sf(vec) sf::Vector2f(vec.x * box2sfRatio, vec.y * box2sfRatio)
#define sf2al(vec) vec.x * sf2alRatio, 0, vec.y * sf2alRatio

#define sqr(x) x*x

#define explode(vec) vec.x, vec.y
