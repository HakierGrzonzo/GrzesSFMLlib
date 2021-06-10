#include "Bullet.hpp"
#include "../../funcs.hpp"
#include "../../Component/templates/Bullet.hpp"
#include "../../Component/templates/BulletSound.hpp"
#include "../../Component/templates/sprites/Bullet.hpp"

namespace entity {
    Bullet::Bullet(
        utils::Position position_,
        EntitySystem* scene_
    ) : Entity(position_, entityTags::bullet, scene_) {}

    void Bullet::Initialize() {
        add_component(component::Bullet);
        add_component(component::sprites::Bullet);
        add_component(component::BulletSound);
    }
}
