#include "Background.hpp"
#include "../../funcs.hpp"
#include "../../Component/templates/sprites/Background.hpp"

namespace entity {
    background::background(EntitySystem* scene_)
        : entity::Entity(utils::Position(), entityTags::visual, scene_) {
    }
    void background::Initialize() {
        add_component(component::shadedBackground);
    }

    void background::LateInitialize() {}
}
