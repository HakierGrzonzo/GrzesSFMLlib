#include "Debug.hpp"
#include <iostream>
#include <string>

#define printId(var) std::cerr << __FILE__ << ": " << id << " ->\t" << var << std::endl; std::cerr.flush()

namespace component {
    Debug::Debug(entity::Entity* parent_) : Component(parent_) {
        id = idCounter++;
    }

    void Debug::Awake() {
    }

    void Debug::Update() {
        //printId(parent->scene->getEntitiesInRadius(parent, 4000).size());
    }

    void Debug::FixedUpdate(double timestep) {
    }

    void Debug::LateFixedUpdate() {
    }

    Debug::~Debug() {
    }

    unsigned int Debug::idCounter = 0;
}
