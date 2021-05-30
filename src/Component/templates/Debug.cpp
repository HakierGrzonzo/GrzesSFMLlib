#include "Debug.hpp"
#include <iostream>
#include <string>

#define printId(var) std::cerr << __FILE__ << ": " << id << " ->\t" << var << std::endl; std::cerr.flush()

namespace component {
    Debug::Debug(entity::Entity* parent_) : Component(parent_) {
        id = idCounter++;
        printId("Constructor");
    }

    void Debug::Awake() {
        printId("Awake()");
    }

    void Debug::Update() {
        printId("Update()");
    }

    void Debug::FixedUpdate(double timestep) {
        printId("FixedUpdate(" + std::to_string(timestep) + ")");
    }

    void Debug::LateFixedUpdate() {
        printId("LateFixedUpdate()");
    }

    Debug::~Debug() {
        printId("Deconstructor");
    }

    unsigned int Debug::idCounter = 0;
}
