#pragma once

#include "Physics.hpp"
#include "Sprite.hpp"

namespace component {
    class StaticBody : public PhysicsBody {
        public:
            StaticBody(entity::Entity* parent_);
            void Awake();
            void Update();
        private:
            bool isFullyInit;
    };
}
