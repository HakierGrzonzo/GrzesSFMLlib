#pragma once

#include "../Sprite.hpp"

namespace component {
    namespace sprites {
        class player : public component::SpriteRenderer {
        public:
            player(entity::Entity* parent_);
            void Initialize();
        };
    }
}
