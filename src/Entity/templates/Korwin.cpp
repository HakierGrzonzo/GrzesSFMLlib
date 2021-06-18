#include "Korwin.hpp"
#include "../../funcs.hpp"
#include "../../Component/templates/Korwin.hpp"
#include "../../Component/templates/Physics.hpp"
#include "../../Component/templates/Enemy.hpp"
#include "../../Component/templates/EnemyController.hpp"

namespace entity {
    namespace tests {      
        korwintest::korwintest(utils::Position position_, EntitySystem* scene_) 
            : entity::Entity(position_, entityTags::enemy, scene_) {
        }
        void korwintest::Initialize() {
            add_component(component::sprites::korwin);
            add_component(component::PhysicsBody);
            add_component(component::Enemy);
            add_component(component::EnemyController);
        }
        void korwintest::LateInitialize() {
            component::PhysicsBody* physics = GetComponent<component::PhysicsBody>();
            assertCond(physics == nullptr, "no physics body");
            physics->body->SetLinearDamping(8);
            scene->audioScene.addSource(
                    scene->getWeakPtr(this),
                    "sfx/walk.wav.aac",
                    1,
                    true
                );
        }
    }
}
