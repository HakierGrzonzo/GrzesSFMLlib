#include "Entity-Background.hpp"
#include "Entity-System.hpp"
#include "Entity-Tags.hpp"
#include "Utils-Position.hpp"
#include "funcs.hpp"
#include "Component-Shaded-Background.hpp"

namespace entity {
    background::background(const EntitySystem* scene_)
        : entity::Entity(utils::Position(), entityTags::visual, scene_) {
        Initialize();
    }
    void background::Initialize() {
        add_component(component::shadedBackground);
    }

    void background::LateInitialize() {}
}
