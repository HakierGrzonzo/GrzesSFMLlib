#pragma once
#include "../Gun.hpp"
#include "../Bullet.hpp"

namespace component {
    namespace guns {
        class Pistol : public Gun {
            public:
                Pistol(entity::Entity* parent_);
                void Shoot();
                void FixedUpdate(double timeStep);
            protected:
                double timeSinceLastShot;
                double shootingSpeed;
                int bulletDamage;
        };
    }
}
