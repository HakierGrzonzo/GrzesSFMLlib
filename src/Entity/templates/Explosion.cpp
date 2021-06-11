#include "Explosion.hpp"
#include "../../funcs.hpp"

namespace entity {
    Explosion::Explosion(utils::Position position, EntitySystem* scene) : 
        Entity(position, visual, scene){}

    void Explosion::Initialize() {
        add_component(component::Explosion);
    }
}
