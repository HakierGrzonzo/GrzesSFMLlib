#pragma once
#include "../ShadedSprite.hpp"

namespace component {
    namespace sprites {
        class Bullet : public ShadedSpriteRenderer {
            public:
                Bullet(entity::Entity* parent_);
                void FixedUpdate(double timeStep);
                void LateFixedUpdate();
                void Initialize();
            private:
                float renderCounter;
        };
    }
}
