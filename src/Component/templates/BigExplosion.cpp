#include "BigExplosion.hpp"

namespace component {
    BigExplosion::BigExplosion(entity::Entity* parent_) :
        Explosion(parent_) {
            range = 800;
        }

    int BigExplosion::dealDamege(float distance) {
        return 10;
    }
}
