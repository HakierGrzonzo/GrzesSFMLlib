#pragma once

#include "../Sprite.hpp"

namespace component {
    namespace sprites {
        class testSprite : public component::SpriteRenderer {
        public:
            testSprite(entity::Entity* parent_);
            void Initialize();
        };
    }
}
