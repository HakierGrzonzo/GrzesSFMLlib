#include "EnemyTarget.hpp"
#include "../../funcs.hpp"

namespace component {
    EnemyTarget::EnemyTarget(entity::Entity* parent_) : Component(parent_) {
        sinceTick = 0;
    }
    
    int EnemyTarget::getPriority() {
        return priority;
    }

    void EnemyTarget::Awake() {
        priority = 10;
    }
    
    void EnemyTarget::modifyPriority(int modifyBy) {
        priority += modifyBy;
    }

    void EnemyTarget::FixedUpdate(double timeDelta) {
        sinceTick += timeDelta;
        while (sinceTick > 10) {
            priority--;
            if (priority <= 0) {
                parent->scene->deleteEntity(parent);
                break;
            }
        }
    }
}
