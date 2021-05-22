#pragma once

#include "Component.hpp"
#include "Entity.hpp"
#include "Component-Sprite.hpp"

namespace component {
    namespace sprites {
        class player : public component::SpriteRenderer {
        public:
            player(entity::Entity* parent_);
            void Initialize();
        };
    }
}
