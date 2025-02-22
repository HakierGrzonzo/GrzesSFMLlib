#include "Player.hpp"
#include "../../funcs.hpp"
#include "../../Component/templates/Physics.hpp"
#include "../../Component/templates/Player.hpp"
#include "../../Component/templates/playerControler.hpp"
#include "../../Component/templates/Debug.hpp"
#include "../../Component/templates/sprites/Player.hpp"
#include "../../Component/templates/guns/Pistol.hpp"
#include "../../Component/templates/spawners/Test.hpp"
#include "Korwin.hpp"
#include <box2d/b2_math.h>

namespace entity {
    playerEntity::playerEntity(utils::Position position_, EntitySystem* scene_) 
        : entity::Entity(position_, entityTags::player, scene_) {
    }

    void playerEntity::Initialize() {
        add_component(component::sprites::player);
        add_component(component::PhysicsBody);
        add_component(component::Player);
        add_component(component::PlayerControler);
        add_component(component::guns::Pistol);
        add_component(component::spawners::Generic<tests::korwintest>);
    }
    
    void playerEntity::LateInitialize() {
        component::PhysicsBody* physics = GetComponent<component::PhysicsBody>();
        assertCond(physics == nullptr, "no physics body");
        physics->body->SetLinearDamping(2);
        auto spawner = GetComponent<component::Spawner>();
        assertCond(spawner == nullptr, "Spawner is missing");
        spawner->startSpawning(1, 4000, -1);
        scene->audioScene.addSource(
                scene->getWeakPtr(this),
                "test.aac",
                1,
                true
            );
    }
}
