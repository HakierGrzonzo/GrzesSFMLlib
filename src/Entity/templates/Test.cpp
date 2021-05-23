#include "Test.hpp"
#include "../../funcs.hpp"
#include "../../Component/templates/sprites/Test.hpp"

namespace entity {
    testEntity::testEntity(utils::Position position_, EntitySystem* scene_) 
        : entity::Entity(position_, entityTags::test, scene_) {
        Initialize();
    }

    void testEntity::Initialize() {
        add_component(component::sprites::testSprite);
    }
    testEntity::~testEntity() {}
}
