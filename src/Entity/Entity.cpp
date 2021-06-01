#include "Entity.hpp"
#include "Entity-System.hpp"
#include "Entity-Tags.hpp"
#include <memory>
#include <typeinfo>


namespace entity {
    Entity::Entity(utils::Position position_, entityTags tag_, EntitySystem* scene_) {
        position = position_;
        tag = tag_;
        components = std::vector<std::unique_ptr<component::Component>>();
        scene = scene_;
        Initialize();
    }
    void Entity::Initialize() {}
    void Entity::LateInitialize() {}
    Entity::~Entity() {}
}
