#include "Wall.hpp"
#include "../../funcs.hpp"
#include "../../Component/templates/StaticPhysics.hpp"
#include "../../Component/templates/sprites/Wall.hpp"

namespace entity {
    Wall::Wall(
        utils::Position position_,
        EntitySystem* scene_
    ) : Entity(position_, entityTags::visual, scene_) {}

    void Wall::Initialize() {
        add_component(component::StaticBody);
        add_component(component::sprites::Wall);
    }
}
