#include "Entity.hpp"
#include "Component.hpp"
#include "EntityTags.hpp"
#include <memory>
#include <typeinfo>


namespace entity {
    Entity::Entity(utils::Position position_, entityTags tag_) {
        position = position_;
        tag = tag_;
        components = std::vector<std::unique_ptr<component::Component>>();
        Initialize();
    }
    void Entity::Initialize() {}
}
