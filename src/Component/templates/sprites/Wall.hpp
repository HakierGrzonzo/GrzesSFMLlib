#pragma once

#include "../Sprite.hpp"

namespace component {
    namespace sprites {
        class Wall : public component::SpriteRenderer {
        public:
            Wall(entity::Entity* parent_);
            void Initialize();
        };
    }
}
