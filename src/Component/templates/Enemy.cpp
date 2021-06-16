#include "Enemy.hpp"
#include "../../Entity/templates/Target.hpp"
#include "../../Entity/templates/BigExplosion.hpp"

namespace component {
    Enemy::Enemy(entity::Entity* parent_) : Creature(parent_) {
        maxHP = 20;
        hp = 20;
    }

    void Enemy::onDeathHook() {
        parent->scene->addEntity(
            new entity::Target(
                parent->position, 
                parent->scene
                ), entity::back
        );
        parent->scene->addEntity(
                new entity::BigExplosion(
                    parent->position,
                    parent->scene
                ), entity::top
        );
    }
}
