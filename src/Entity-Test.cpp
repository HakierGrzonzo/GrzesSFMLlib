#include "Entity-Test.hpp"
#include "Entity-System.hpp"
#include "Entity-Tags.hpp"
#include "Utils-Position.hpp"
#include "funcs.hpp"
#include "Component-Sprite-Test.hpp"

namespace entity {
    testEntity::testEntity(utils::Position position_, const EntitySystem* scene_) 
        : entity::Entity(position_, entityTags::test, scene_) {
        Initialize();
    }

    void testEntity::Initialize() {
        add_component(component::sprites::testSprite);
    }

}
