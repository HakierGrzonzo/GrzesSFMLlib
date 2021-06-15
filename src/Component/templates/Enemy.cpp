#include "Enemy.hpp"
#include "../../Entity/templates/Target.hpp"

namespace component {
    Enemy::Enemy(entity::Entity* parent_) : Creature(parent_) {}

    void Enemy::onDeathHook() {
        parent->scene->addEntity(
            new entity::Target(parent->position, parent->scene)
        );
    }
}
