#include "EnemyController.hpp"
#include "EnemyTarget.hpp"
#include "Physics.hpp"
#include "../../funcs.hpp"
#include <memory>

float getScore(int priority, float distance) {
    return (1/distance) * sqr(priority);
}

#define TARGET_SEP 1000

float getEnemyScore(float distance) {
    if (distance > 2 * TARGET_SEP) {
        return 0;
    }
    return (distance - TARGET_SEP) / TARGET_SEP;
}

namespace component {
    EnemyController::EnemyController(entity::Entity* parent_) : Component(parent_) {

    }

    void EnemyController::Update() {
        auto targets = parent->scene->getEntitiesInRadius(
            parent,
            10000,
            entity::target,
            false
        );
        auto phys = parent->GetComponent<component::PhysicsBody>();
        assertNotNull(phys);
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
            movment.x /= 10;
            movment.y /= 10;
            phys->body->ApplyForceToCenter(movment, true);
        }
        // calculate force to not bump into other enemies but to group up
        auto otherEnemies = parent->scene->getEntitiesInRadius(
                parent,
                2 * TARGET_SEP,
                entity::enemy,
                false
        );
        for (auto otherEnemy : otherEnemies) {
            auto physRef = otherEnemy.lock()->GetComponent<PhysicsBody>();
            assertNotNull(physRef);
            auto direction = otherEnemy.lock()->position.xy - parent->position.xy;
            auto force = sf2box(direction);
            force.Normalize();
            auto distance = parent->position.distanceTo(otherEnemy.lock()->position);
            force *= getEnemyScore(distance) * .2;
            phys->body->ApplyForceToCenter(force, true);
        }
    }
}
