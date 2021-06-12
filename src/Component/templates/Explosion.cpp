#include "Explosion.hpp"
#include "Creature.hpp"
#include "../../funcs.hpp"

namespace component {
    Explosion::Explosion(entity::Entity* parent) : Component(parent) {
        hadExploded = false;
        range = 400;
    }
    
    float Explosion::getRange() {
        return range;
    }

    void Explosion::Update() {
        if (!hadExploded) {
            hadExploded = true;
            auto targets = parent->scene->getEntitiesInRadius(
                    parent,
                    range
            );
            for (unsigned long long i = 0; i < targets.size(); i++) {
                auto creature = targets[i].lock()->GetComponent<Creature>();
                // if that entity has a creature
                if (creature) {
                    // call dealDamage with normalized distance
                    creature->changeHP(-dealDamage(1 -
                        parent->position.distanceTo(targets[i].lock()->position)
                        / range
                    ));
                }
            }
        }
    }

    int Explosion::dealDamage(float distance) {
        return 20 * fmin(.3 + distance, 1);
    }
}
