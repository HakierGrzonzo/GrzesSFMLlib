#pragma once

#include "../Entity.hpp"

namespace entity {
    class playerEntity : public Entity {
        public:
            playerEntity(utils::Position position_, EntitySystem* scene_);
            void Initialize();
            void LateInitialize();
    };
}
