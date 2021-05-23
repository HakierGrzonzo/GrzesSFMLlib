#include "Creature.hpp"

namespace component {
    Creature::Creature(entity::Entity* parent_) : Component(parent_) {
        hp = 100;
        maxHP = hp;
    }
    void Creature::FixedUpdate(double timeDelta) {
        if (hp == 0) {
            parent->scene->deleteEntity(parent);
        }
    }

    Creature::~Creature() {}

    
}
