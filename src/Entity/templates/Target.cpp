#include "Target.hpp"
#include "../../funcs.hpp"
#include "../../Component/templates/EnemyTarget.hpp"

namespace entity {
    Target::Target(utils::Position pos, entity::EntitySystem* scene) : 
        Entity(pos, target, scene) {}

    void Target::Initialize() {
        add_component(component::EnemyTarget);
    }
}
