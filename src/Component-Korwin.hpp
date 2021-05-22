#pragma once
#include "Component.hpp"
#include "Component-Shaded-Sprite.hpp"

namespace component {
    namespace sprites {
        class korwin : public component::ShadedSpriteRenderer {
        public:
            korwin(entity::Entity* parent_);
            void Initialize();
            void FixedUpdate(double timeDelta);
        private: 
            float renderCounter;
        };
    }
}
