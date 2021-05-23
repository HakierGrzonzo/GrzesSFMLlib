#include "../../Component/templates/Korwin.hpp"
#include "../../funcs.hpp"
#include "Korwin.hpp"
#include "../../Component/templates/Physics.hpp"

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
