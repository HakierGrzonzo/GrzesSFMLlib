#include "BigExplosion.hpp"
#include "../../Component/templates/sprites/Explosion.hpp"
#include "../../funcs.hpp"

namespace entity {
    BigExplosion::BigExplosion(utils::Position position, EntitySystem* scene) : 
        Entity(position, visual, scene){}

    void BigExplosion::Initialize() {
        add_component(component::BigExplosion);
        add_component(component::sprites::Explosion);
    }
}
