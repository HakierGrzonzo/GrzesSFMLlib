#include "Component-Korwin.hpp"
#include "funcs.hpp"
#include "Entity-Korwin.hpp"
#include "Component-Physics.hpp"

namespace entity {
    namespace tests {      
        korwintest::korwintest(utils::Position position_, const EntitySystem* scene_) 
            : entity::Entity(position_, entityTags::enemy, scene_) {
            Initialize();
        }
        void korwintest::Initialize() {
            add_component(component::sprites::korwin);
            add_component(component::PhysicsBody);
        }
        void korwintest::LateInitialize() {
            component::PhysicsBody* physics = GetComponent<component::PhysicsBody>();
            assertCond(physics == nullptr, "no physics body");
            physics->body->SetLinearDamping(8);
        }
    }
}
