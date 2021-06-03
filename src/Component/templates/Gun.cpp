#include "Gun.hpp"
#include <SFML/Window/Keyboard.hpp>

namespace component {
    Gun::Gun(entity::Entity* parent_) : Component(parent_) {}

    void Gun::Awake() {
        callback = parent->scene->inputHandler.subscribe(sf::Keyboard::Space, this->ShootCallback, this);
    }

    void Gun::ShootCallback(void* ptr) {
        Gun* thisPtr = (Gun*) ptr;
        thisPtr->Shoot();
    }
}
