#include "Player.hpp"
#include "../../funcs.hpp"
#include "../../Component/templates/Physics.hpp"
#include "../../Component/templates/Creature.hpp"
#include "../../Component/templates/playerControler.hpp"
#include "../../Component/templates/Debug.hpp"
#include "../../Component/templates/sprites/Player.hpp"
#include "../../Component/templates/guns/Pistol.hpp"
#include <box2d/b2_math.h>

namespace entity {
    playerEntity::playerEntity(utils::Position position_, EntitySystem* scene_) 
        : entity::Entity(position_, entityTags::player, scene_) {
    }

    void playerEntity::Initialize() {
        add_component(component::sprites::player);
        add_component(component::PhysicsBody);
        add_component(component::Creature);
        add_component(component::PlayerControler);
        add_component(component::guns::Pistol);
    }
    
    void playerEntity::LateInitialize() {
        component::PhysicsBody* physics = GetComponent<component::PhysicsBody>();
        assertCond(physics == nullptr, "no physics body");
        physics->body->SetLinearDamping(2);
    }
}
