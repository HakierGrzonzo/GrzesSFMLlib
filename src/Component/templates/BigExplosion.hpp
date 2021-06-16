#pragma once
#include "Explosion.hpp"

namespace component {
    class BigExplosion : public Explosion {
        public: 
            BigExplosion(entity::Entity* parent_);
            int dealDamege(float distance);
    };
}
