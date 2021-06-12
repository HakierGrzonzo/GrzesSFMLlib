#include "Explosion.hpp"
#include "../../Component/templates/sprites/Explosion.hpp"
#include "../../funcs.hpp"

namespace entity {
    Explosion::Explosion(utils::Position position, EntitySystem* scene) : 
        Entity(position, visual, scene){}

    void Explosion::Initialize() {
        add_component(component::Explosion);
        add_component(component::sprites::Explosion);
    }
}
