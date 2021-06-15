#include "EnemyController.hpp"
#include "Physics.hpp"
#include "../../funcs.hpp"
#include <memory>

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
        if (targets.size() > 0) {
            std::weak_ptr<entity::Entity> closest;
            float lastDistance = INFINITY;
            for (auto target : targets) {
                auto distance = parent->position.distanceTo(target.lock()->position);
                print(distance);
                if (distance < lastDistance) {
                    closest = target;
                    lastDistance = distance;
                }
            }
            auto phys = parent->GetComponent<component::PhysicsBody>();
            assertNotNull(phys);
            auto direction = closest.lock()->position.xy - parent->position.xy;
            auto movment = sf2box(direction);
            movment.Normalize();
            movment.x /= 10;
            movment.y /= 10;
            phys->body->ApplyForceToCenter(movment, true);
        }
    }
}
