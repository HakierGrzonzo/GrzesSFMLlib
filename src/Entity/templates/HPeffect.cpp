#include "HPeffect.hpp"
#include "../../funcs.hpp"
#include "../../Component/templates/sprites/HPeffect.hpp"

namespace entity {
    HPeffect::HPeffect(utils::Position position_, EntitySystem* scene_) 
        : entity::Entity(position_, entityTags::visual, scene_) {
    }

    void HPeffect::Initialize() {
        add_component(component::sprites::HPeffect);
    }
    HPeffect::~HPeffect() {}
}
