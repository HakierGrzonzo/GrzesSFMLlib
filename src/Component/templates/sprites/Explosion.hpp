#pragma once
#include "../ShadedSprite.hpp"

namespace component {
    namespace sprites {
        class Explosion : public ShadedSpriteRenderer {
            public:
                Explosion(entity::Entity* parent_);
                void Update();
                void FixedUpdate(double timeStep);
                void LateFixedUpdate();
                void Initialize();
            private:
                float renderCounter;
                float length;
        };
    }
}
