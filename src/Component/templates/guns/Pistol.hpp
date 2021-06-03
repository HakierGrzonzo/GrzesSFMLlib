#pragma once
#include "../Gun.hpp"
#include "../Bullet.hpp"

namespace component {
    namespace guns {
        class Pistol : public Gun {
            public:
                Pistol(entity::Entity* parent_);
                void Shoot();
            protected:
                double timeSinceLastShot;
                double shootingSpeed;
                int bulletDamage;
        };
    }
}
