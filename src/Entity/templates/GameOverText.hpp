#pragma once

#include "../Entity.hpp"

namespace entity {
    class GameOverText : public Entity {
        public:
            GameOverText(utils::Position position_, EntitySystem* scene_);
            void Initialize();
    };
}
