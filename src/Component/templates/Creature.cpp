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
        else if (hp > maxHP) {
            hp = maxHP;
        }
    }
    void Creature::setHP(unsigned int newHp) {
        if (newHp > maxHP) {
            hp = maxHP;
        }
        else {
            hp = newHp;
        }
    }

    unsigned int Creature::getHP() {
        return hp;
    }

    unsigned int Creature::getMaxHP() {
        return maxHP;
    }

    void Creature::setMaxHP(unsigned int hp_) {
        maxHP = hp_;
    }
    unsigned int Creature::changeHP(int changeBy) {
        // check for overflow
        long long int newHp = (long long int) hp + (long long int) changeBy;
        if (newHp <= 0) hp = 0;
        else if (newHp >= maxHP) hp = maxHP;
        // if safe add
        else hp = hp + changeBy;
        return hp;
    }

    Creature::~Creature() {}

    
}
