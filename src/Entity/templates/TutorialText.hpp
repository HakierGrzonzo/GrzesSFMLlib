#pragma once

#include "../Entity.hpp"

namespace entity {
    class TutorialText : public Entity {
        public:
            TutorialText(utils::Position position_, EntitySystem* scene_);
            void Initialize();
    };
}
