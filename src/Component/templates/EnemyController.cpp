#include "EnemyController.hpp"
#include "EnemyTarget.hpp"
#include "Explosion.hpp"
#include "Physics.hpp"
#include "../../funcs.hpp"
#include "Enemy.hpp"
#include <memory>

float getScore(int priority, float distance) {
    return (1/distance) * sqr(priority);
}

#define TARGET_SEP 1000
#define DETONATION 300
#define LOCK_ON 3000

float getEnemyScore(float distance) {
    if (distance > 2 * TARGET_SEP) {
        return 0;
    }
    return (distance - TARGET_SEP) / TARGET_SEP;
}

namespace component {
    EnemyController::EnemyController(entity::Entity* parent_) : Component(parent_) {
        try {
            player = parent->scene->GetEntityByTag(entity::player);
        } catch (...) {}
        isPlayerDead = false;
    }

    void EnemyController::Update() {
        auto phys = parent->GetComponent<component::PhysicsBody>();
        assertNotNull(phys);
        bool playerInRange = false;
        // get other nearby enemies
        auto otherEnemies = parent->scene->getEntitiesInRadius(
                parent,
                2 * TARGET_SEP,
                entity::enemy,
                false
        );
        // if player in range go to him
        if (!player.expired()) {
            auto playerRef = player.lock();
            if (
                    float distance = parent->position.distanceTo(playerRef->position); 
                    distance < LOCK_ON * 2)
                {
                // sleep when far away
                if (distance > 5 * LOCK_ON) return;
                if (distance < 300) {
                    auto creature = parent->GetComponent<Enemy>();
                    assertNotNull(creature);
                    creature->setHP(0);
                    return;
                }
                playerInRange = true;
                auto direction = playerRef->position.xy - parent->position.xy;
                auto movment = sf2box(direction);
                movment.Normalize();
                movment.x /= 4;
                movment.y /= 4;
                // If I am alone -> run away
                if (otherEnemies.size() < 2 && distance < LOCK_ON * 2 && 
                        distance > LOCK_ON) {
                    movment = -movment;
                }
                phys->body->ApplyForceToCenter(movment, true);
            }
        } else if (!isPlayerDead) {
            try {
                player = parent->scene->GetEntityByTag(entity::player);
            } catch (...) {
                isPlayerDead = true;
            }
        }
        // if player is not in range
        if (!playerInRange) {
            auto targets = parent->scene->getEntitiesInRadius(
                parent,
                5000,
                entity::target,
                false
            );
            if (targets.size() > 0) {
                std::weak_ptr<entity::Entity> closest;
                float lastScore = -1;
                for (auto target : targets) {
                    auto distance = parent->position.distanceTo(target.lock()->position);
                    auto targetRef = target.lock()->GetComponent<EnemyTarget>();
                    assertNotNull(targetRef);
                    // if close lower priority
                    if (
                            distance < 800 &&
                            (lastVisitedEntity.expired() ? nullptr : lastVisitedEntity.lock().get())
                                != target.lock().get()
                        ) {
                        targetRef->modifyPriority(-1);
                        lastVisitedEntity = target;
                    }
                    float score = getScore(targetRef->getPriority(), distance);
                    if (score > lastScore) {
                        closest = target;
                        lastScore = score;
                    }
                }
                auto direction = closest.lock()->position.xy - parent->position.xy;
                auto movment = sf2box(direction);
                movment.Normalize();
                movment.x /= 20;
                movment.y /= 20;
                phys->body->ApplyForceToCenter(movment, true);
            }
        }
        // calculate force to not bump into other enemies but to group up
        for (auto otherEnemy : otherEnemies) {
            auto physRef = otherEnemy.lock()->GetComponent<PhysicsBody>();
            assertNotNull(physRef);
            auto direction = otherEnemy.lock()->position.xy - parent->position.xy;
            auto force = sf2box(direction);
            force.Normalize();
            auto distance = parent->position.distanceTo(otherEnemy.lock()->position);
            force *= getEnemyScore(distance) * .1;
            phys->body->ApplyForceToCenter(force, true);
        }

    }
}
